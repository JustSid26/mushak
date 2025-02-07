import YdLidarX2 as ydlidar_x2
import time
import numpy as np
import pandas as pd
import joblib
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backend_bases import MouseEvent

rf_classifier = joblib.load(r'D:\Python\NasaHerc 2025\random_forest_model.pkl')
label_encoder = joblib.load(r'D:\Python\NasaHerc 2025\label_encoder.pkl')

port = 'COM5'
lid = ydlidar_x2.YDLidarX2(port)

if lid.connect():
    print("Connected to YDLidarX2 on port", port)
    lid.start_scan()

    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
    ax.set_theta_zero_location('N')  
    ax.set_theta_direction(-1)
    scatter = ax.scatter([], [], s=10, c='blue', label="Distance Points")
    ax.set_rmax(7000) 

    laser_line, = ax.plot([], [], color='red', label="Laser Pointer")
    laser_distance_text = ax.text(0.5, 0.9, "", transform=ax.transAxes, ha='center', va='center')

    timer_text = ax.text(0.5, 0.85, "", transform=ax.transAxes, ha='center', va='center', color='green')

    laser_data = {'angle': None, 'distance': None}

    last_sample_time = time.time()
    sampling_interval = 2

    def preprocess_lidar_data(angles, distances):
        valid = distances > 0

        exclude_range = (angles < np.radians(135)) | (angles > np.radians(225))
        valid = valid & exclude_range

        angles = angles[valid]
        distances = distances[valid]

        data = {'angle': angles, 'distance': distances}
        df = pd.DataFrame(data)

        return df

    def make_prediction(lidar_data):
        processed_data = preprocess_lidar_data(lidar_data['angle'], lidar_data['distance'])

        prediction = rf_classifier.predict(processed_data)

        decoded_prediction = label_encoder.inverse_transform(prediction)
        return decoded_prediction[0]

    def update(frame):
        global last_sample_time
        current_time = time.time()

        time_remaining = max(0, sampling_interval - (current_time - last_sample_time))
        timer_text.set_text(f"Next sample in: {time_remaining:.1f}s")

        if current_time - last_sample_time >= sampling_interval:
            if lid.available:
                data = lid.get_data()
                angles = np.radians(np.arange(len(data))) 
                distances = np.array(data)

                lidar_data = {'angle': angles, 'distance': distances}
                prediction = make_prediction(lidar_data)
                print(f"Prediction: {prediction}")

                scatter.set_offsets(np.c_[angles, distances])

                if laser_data['angle'] is not None:
                    angle_diff = np.abs(angles - laser_data['angle'])
                    closest_idx = np.argmin(angle_diff)
                    laser_data['distance'] = distances[closest_idx]


                    laser_line.set_data([laser_data['angle'], laser_data['angle']], [0, laser_data['distance']])
                    laser_distance_text.set_text(f"Distance: {laser_data['distance']} mm")

            last_sample_time = current_time

        return scatter, laser_line, laser_distance_text, timer_text

    def on_click(event: MouseEvent):
        if event.inaxes == ax:

            laser_data['angle'] = event.xdata
            if laser_data['angle'] < 0:
                laser_data['angle'] += 2 * np.pi 

            update(0)

    fig.canvas.mpl_connect('button_press_event', on_click)

    ani = FuncAnimation(fig, update, interval=100) 
    try:
        plt.legend(loc='upper right')
        plt.title("Real-Time Lidar Visualization with Laser Pointer")
        plt.show()
    except KeyboardInterrupt:
        print("Visualization interrupted by user.")
    finally:
        lid.stop_scan()
        lid.disconnect()
        print("Lidar stopped and disconnected. Done.")
else:
    print(f"Failed to connect to YDLidarX2 on port {port}")
