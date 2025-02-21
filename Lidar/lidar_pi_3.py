import socket
import json
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# UDP Socket setup
PORT = 5005
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("", PORT))

print(f"Listening for Lidar data on port {PORT}...")

# Visualization setup
fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
ax.set_theta_zero_location("N")  # North at the top
ax.set_theta_direction(-1)  # Clockwise
scatter = ax.scatter([], [], s=10, c="blue", label="Distance Points")
ax.set_rmax(7000)  # Max range (in mm)

# Function to update the plot
def update(frame):
    data, addr = sock.recvfrom(65536)  # Receive data
    lidar_data = json.loads(data.decode())

    angles = np.array(lidar_data["angles"])
    distances = np.array(lidar_data["distances"])

    # Update scatter plot
    scatter.set_offsets(np.c_[angles, distances])
    return scatter,

# Animate the plot
ani = FuncAnimation(fig, update, interval=50)  # Update every 50ms

plt.legend(loc="upper right")
plt.title("Real-Time Lidar Visualization (UDP Receiver)")
plt.show()
