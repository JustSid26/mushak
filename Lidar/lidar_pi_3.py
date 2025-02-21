import socket
import json
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.backend_bases import MouseEvent

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

# Laser pointer setup
laser_data = {"angle": None, "distance": None}
laser_line, = ax.plot([], [], color="red", label="Laser Pointer")
laser_distance_text = ax.text(0.5, 0.9, "", transform=ax.transAxes, ha="center", va="center")

# Function to update the plot
def update(frame):
    data, addr = sock.recvfrom(65536)  # Receive data
    lidar_data = json.loads(data.decode())

    angles = np.array(lidar_data["angles"])
    distances = np.array(lidar_data["distances"])

    # Update scatter plot
    scatter.set_offsets(np.c_[angles, distances])

    # Update laser pointer if set
    if laser_data["angle"] is not None:
        # Find the closest angle match
        angle_diff = np.abs(angles - laser_data["angle"])
        closest_idx = np.argmin(angle_diff)
        laser_data["distance"] = distances[closest_idx]

        # Update laser pointer line
        laser_line.set_data([laser_data["angle"], laser_data["angle"]], [0, laser_data["distance"]])
        laser_distance_text.set_text(f"Distance: {laser_data['distance']} mm")

    return scatter, laser_line, laser_distance_text

# Mouse event to capture the laser pointer direction
def on_click(event: MouseEvent):
    if event.inaxes == ax:
        laser_data["angle"] = event.xdata
        if laser_data["angle"] < 0:
            laser_data["angle"] += 2 * np.pi  # Ensure positive angle

        # Force an update to display the laser pointer
        update(0)

fig.canvas.mpl_connect("button_press_event", on_click)

# Animate the plot
ani = FuncAnimation(fig, update, interval=50)  # Update every 50ms

plt.legend(loc="upper right")
plt.title("Real-Time Lidar Visualization with Laser Pointer (UDP Receiver)")
plt.show()
