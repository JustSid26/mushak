import serial
import serial.tools.list_ports
import time
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backend_bases import MouseEvent
import tkinter as tk
from tkinter import simpledialog

import os
import YdLidarX2 as ydlidar_x2

# Auto-detect the correct port for CP210x
def find_cp210x_device():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if "CP210" in port.description:  # Check if it's CP210x UART Bridge
            return port.device  
    return None

port = find_cp210x_device()

if not port:
    print("Error: CP210x UART Bridge device not found!")
    exit()

print(f"Connecting to YDLidarX2 on {port}...")
lid = ydlidar_x2.YDLidarX2(port)

# Ensure files exist
for file_name in ["Object_1_Readings.txt", "Object_2_Readings.txt"]:
    if not os.path.exists(file_name):
        with open(file_name, "w") as f:
            f.write("Angle (radians), Distance (mm)\n")

# --- Object Selection Window ---
def select_object():
    root = tk.Tk()
    root.title("Select Object")
    root.geometry("300x150")
    
    selection = tk.StringVar(value="None")

    def set_object(value):
        selection.set(value)
        root.destroy()

    label = tk.Label(root, text="Select which object to save data for:", font=("Arial", 12))
    label.pack(pady=10)

    button1 = tk.Button(root, text="Object 1", font=("Arial", 10), command=lambda: set_object("Object 1"))
    button1.pack(pady=5)

    button2 = tk.Button(root, text="Object 2", font=("Arial", 10), command=lambda: set_object("Object 2"))
    button2.pack(pady=5)

    root.mainloop()
    return selection.get()

selected_object = select_object()

if selected_object == "None":
    print("No object selected. Exiting.")
    exit()

# Determine filename based on selection
file_name = "Object_1_Readings.txt" if selected_object == "Object 1" else "Object_2_Readings.txt"

# Check connection
if lid.connect():
    print("Connected successfully.")
    lid.start_scan()

    # Visualization setup
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
    ax.set_theta_zero_location('N')
    ax.set_theta_direction(-1)
    scatter = ax.scatter([], [], s=10, c='blue', label="Distance Points")
    ax.set_rmax(7000)

    # Laser pointer setup
    laser_line, = ax.plot([], [], color='red', label="Laser Pointer")
    laser_distance_text = ax.text(0.5, 0.9, "", transform=ax.transAxes, ha='center', va='center')

    # Timer text
    timer_text = ax.text(0.5, 0.85, "", transform=ax.transAxes, ha='center', va='center', color='green')

    # Storage for laser pointer data
    laser_data = {'angle': None, 'distance': None}

    # Sampling rate
    last_sample_time = time.time()
    sampling_interval = 1 / 100  # 100 Hz

    # Function to update plot
    def update(frame):
        global last_sample_time
        current_time = time.time()

        # Show next sample timer
        time_remaining = max(0, sampling_interval - (current_time - last_sample_time))
        timer_text.set_text(f"Next sample in: {time_remaining:.1f}s")

        if current_time - last_sample_time >= sampling_interval:
            if lid.available:
                data = lid.get_data()
                angles = np.radians(np.arange(len(data)))  # Convert to radians
                distances = np.array(data)

                # Remove invalid readings
                valid = distances > 0
                angles, distances = angles[valid], distances[valid]

                # Update scatter plot
                scatter.set_offsets(np.c_[angles, distances])

                # Update laser pointer if set
                if laser_data['angle'] is not None:
                    angle_diff = np.abs(angles - laser_data['angle'])
                    closest_idx = np.argmin(angle_diff)
                    laser_data['distance'] = distances[closest_idx]

                    laser_line.set_data([laser_data['angle'], laser_data['angle']], [0, laser_data['distance']])
                    laser_distance_text.set_text(f"Distance: {laser_data['distance']} mm")

            last_sample_time = current_time

        return scatter, laser_line, laser_distance_text, timer_text

    # Mouse click event
    def on_click(event: MouseEvent):
        if event.inaxes == ax:
            if event.button == 1:  # Left Click - Move pointer
                laser_data['angle'] = event.xdata
                if laser_data['angle'] < 0:
                    laser_data['angle'] += 2 * np.pi  
                update(0)

            elif event.button == 3:  # Right Click - Save data
                if laser_data['angle'] is None or laser_data['distance'] is None:
                    print("Error: No laser pointer set. Left-click first.")
                    return

                with open(file_name, "a") as f:
                    f.write(f"{laser_data['angle']}, {laser_data['distance']}\n")

                print(f"Saved to {file_name}: Angle={laser_data['angle']:.2f}, Distance={laser_data['distance']:.2f}")

    fig.canvas.mpl_connect('button_press_event', on_click)

    ani = FuncAnimation(fig, update, interval=1)  # Refresh every 1ms

    try:
        plt.legend(loc='upper right')
        plt.title(f"Real-Time Lidar Visualization ({selected_object})")
        plt.show()
    except KeyboardInterrupt:
        print("Visualization interrupted.")
    finally:
        lid.stop_scan()
        lid.disconnect()
        print("Lidar stopped. Exiting.")
else:
    print("Failed to connect to Lidar.")
