import socket
import json
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Socket setup (Receiver)
HOST = "0.0.0.0"  # Listen on all available interfaces
PORT = 5000

# Create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

# Matplotlib setup
fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
ax.set_theta_zero_location('N')  # North at the top
ax.set_theta_direction(-1)  # Clockwise
scatter = ax.scatter([], [], s=10, c='blue', label="Distance Points")
ax.set_rmax(7000)  # Set the maximum range (in mm)

# Function to receive and update plot
def update(frame):
    try:
        data, _ = sock.recvfrom(65536)  # Receive data
        lidar_data = json.loads(data.decode())  # Decode JSON

        angles = np.radians(lidar_data["angles"])  # Convert to radians
        distances = np.array(lidar_data["distances"])

        valid = distances > 0  # Filter valid distances
        angles = angles[valid]
        distances = distances[valid]

        scatter.set_offsets(np.c_[angles, distances])  # Update plot
        print("Received Data:", lidar_data)
    except Exception as e:
        print(f"Error: {e}")

# Start animation
ani = FuncAnimation(fig, update, interval=50)  # Update every 50ms

plt.legend(loc='upper right')
plt.title("Real-Time Lidar Visualization")
plt.show()
