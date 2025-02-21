import YdLidarX2 as ydlidar_x2
import time
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backend_bases import MouseEvent

# Lidar setup
port = '/dev/ttyUSB0'
lid = ydlidar_x2.YDLidarX2(port)

# Check connection
if lid.connect():
    print("Connected to YDLidarX2 on port", port)
    lid.start_scan()

    # Visualization setup
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
    ax.set_theta_zero_location('N')  # North at the top
    ax.set_theta_direction(-1)  # Clockwise
    scatter = ax.scatter([], [], s=10, c='blue', label="Distance Points")
    ax.set_rmax(7000)  # Set the maximum range (in mm)

    # Initialize laser pointer (in polar coordinates)
    laser_line, = ax.plot([], [], color='red', label="Laser Pointer")
    laser_distance_text = ax.text(0.5, 0.9, "", transform=ax.transAxes, ha='center', va='center')

    # Timer text
    timer_text = ax.text(0.5, 0.85, "", transform=ax.transAxes, ha='center', va='center', color='green')

    # Create a dictionary to store laser pointer data
    laser_data = {'angle': None, 'distance': None}

    # Variables to control sampling
    last_sample_time = time.time()
    sampling_interval = 2  # seconds

    # Function to update plot
    def update(frame):
        global last_sample_time
        current_time = time.time()
        
        # Calculate remaining time for the next sample
        time_remaining = max(0, sampling_interval - (current_time - last_sample_time))
        timer_text.set_text(f"Next sample in: {time_remaining:.1f}s")

        # Only sample if the interval has passed
        if current_time - last_sample_time >= sampling_interval:
            if lid.available:
                data = lid.get_data()
                angles = np.radians(np.arange(len(data)))  # Convert angles to radians
                distances = np.array(data)

                # Filter invalid distances
                valid = distances > 0

                angles = angles[valid]
                distances = distances[valid]

                # Update scatter plot with lidar points
                scatter.set_offsets(np.c_[angles, distances])

                # Update laser pointer if a position is selected
                if laser_data['angle'] is not None:
                    # Find the closest lidar point to the laser pointer
                    angle_diff = np.abs(angles - laser_data['angle'])
                    closest_idx = np.argmin(angle_diff)
                    laser_data['distance'] = distances[closest_idx]

                    # Update laser pointer position (polar coordinates)
                    laser_line.set_data([laser_data['angle'], laser_data['angle']], [0, laser_data['distance']])
                    laser_distance_text.set_text(f"Distance: {laser_data['distance']} mm")

            last_sample_time = current_time

        return scatter, laser_line, laser_distance_text, timer_text

    # Mouse event to capture the laser pointer direction
    def on_click(event: MouseEvent):
        if event.inaxes == ax:
            # Get the angle in radians where the mouse was clicked
            laser_data['angle'] = event.xdata
            if laser_data['angle'] < 0:
                laser_data['angle'] += 2 * np.pi  # Ensure angle is positive

            # Trigger plot update
            update(0)

    fig.canvas.mpl_connect('button_press_event', on_click)

    ani = FuncAnimation(fig, update, interval=100)  # Update every 100ms

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
    
