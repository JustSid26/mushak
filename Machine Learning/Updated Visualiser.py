import YdLidarX2 as ydlidar_x2
import time
import numpy as np
import joblib  
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

port = 'COM5'
lid = ydlidar_x2.YDLidarX2(port)

model_path = r'D:\Python\NasaHerc 2025\random_forest_model.pkl'
model = joblib.load(model_path)
print("Pretrained Random Forest model loaded successfully.")

fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
ax.set_theta_zero_location('N')  
ax.set_theta_direction(-1) 
scatter = ax.scatter([], [], s=10, c='blue', label="Valid Points")
prediction_text = ax.text(0.5, 0.9, "", transform=ax.transAxes, ha='center', va='center', fontsize=12, color='red')

ax.set_rmax(800)  

if lid.connect():
    print(f"Connected to YDLidarX2 on port {port}")
    lid.start_scan()

    def update(frame):
        if lid.available and lid.is_scanning:
            data = lid.get_data()
            angles = np.arange(len(data))  
            distances = np.array(data)  

            valid = (distances > 0) & ((angles < 135) | (angles > 225))
            valid_angles = np.radians(angles[valid])  
            valid_distances = distances[valid]

            if len(valid_angles) >= 269:
                selected_angles = valid_angles[:269]
                selected_distances = valid_distances[:269]

                features = np.concatenate((selected_angles, selected_distances))

                if len(features) == 538:
                    prediction = model.predict([features])
                    if len(prediction) > 0:
  
                        print(prediction[-1])
                    else:
                        prediction_text.set_text("Prediction unavailable.")
                else:
                    prediction_text.set_text(f"Invalid feature size: {len(features)}")

            else:
                prediction_text.set_text("Insufficient valid readings.")

            scatter.set_offsets(np.c_[valid_angles, valid_distances])
        else:
            print("Lidar is not scanning. Retrying...")

        return scatter, prediction_text

    ani = FuncAnimation(fig, update, interval=500, cache_frame_data=False) 

    try:
        plt.legend(loc='upper right')
        plt.title("Lidar Point Visualization with Prediction")
        plt.show()
    except KeyboardInterrupt:
        print("Visualization interrupted by user.")
    finally:
        lid.stop_scan()
        lid.disconnect()
        print("Lidar stopped and disconnected. Done.")
else:
    print(f"Failed to connect to YDLidarX2 on port {port}")
