import serial
import struct
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Configure the serial connection
port = '/dev/ttyUSB0'  # Adjust for your system
baud_rate = 115200  # YDLIDAR X2 default baud rate
ser = serial.Serial(port, baud_rate, timeout=0.1)

# Global variables to hold current scan points and annotation
current_points = []  # Each point: (angle, distance, x, y)
annotation = None

def parse_lidar_data(data):
    """
    Parse raw data from the YDLIDAR X2.
    Assumes each point is 4 bytes: 2 bytes for angle and 2 bytes for distance.
    Angle is stored as a uint16 that needs to be divided by 64 to get degrees.
    Distance is stored as a uint16 in millimeters.
    """
    points = []
    # Ensure data length is a multiple of 4
    if len(data) % 4 != 0:
        data = data[:len(data) - (len(data) % 4)]
    for i in range(0, len(data), 4):
        try:
            angle_raw, distance_raw = struct.unpack('<HH', data[i:i+4])
            angle = angle_raw / 64.0            # Convert to degrees
            distance = distance_raw / 1000.0      # Convert mm to meters
            # Convert polar to Cartesian coordinates
            x = distance * math.cos(math.radians(angle))
            y = distance * math.sin(math.radians(angle))
            points.append((angle, distance, x, y))
        except Exception as e:
            print(f"Error parsing data at index {i}: {e}")
    return points

# Set up the matplotlib figure and scatter plot
fig, ax = plt.subplots()
scatter = ax.scatter([], [], c='blue', s=10)
ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_xlabel("X (m)")
ax.set_ylabel("Y (m)")
ax.set_title("YDLIDAR X2 Visualization")

def update(frame):
    """
    Animation update function that reads from the serial port,
    parses the latest data, and updates the scatter plot.
    """
    global current_points
    # Read available data from serial (non-blocking)
    if ser.in_waiting:
        raw_data = ser.read(ser.in_waiting)
        new_points = parse_lidar_data(raw_data)
        if new_points:
            current_points = new_points
            # Extract x and y coordinates for the scatter plot
            coords = [(p[2], p[3]) for p in current_points]
            scatter.set_offsets(coords)
    return scatter,

def on_click(event):
    """
    Event handler that checks if a click is near a plotted point.
    If so, it annotates the point with its measured distance.
    """
    global annotation
    if event.inaxes != ax:
        return
    # Find the nearest point to the click position
    min_dist = float('inf')
    closest_point = None
    for p in current_points:
        dx = event.xdata - p[2]
        dy = event.ydata - p[3]
        d = math.sqrt(dx * dx + dy * dy)
        if d < min_dist:
            min_dist = d
            closest_point = p
    # Threshold for selection (0.1 m)
    if min_dist < 0.1 and closest_point is not None:
        # Remove any existing annotation
        if annotation is not None:
            annotation.remove()
        annotation = ax.annotate(
            f"Distance: {closest_point[1]:.2f} m",
            xy=(closest_point[2], closest_point[3]),
            xytext=(closest_point[2] + 0.2, closest_point[3] + 0.2),
            arrowprops=dict(facecolor='red', arrowstyle="->"),
            fontsize=10,
            color='red'
        )
        plt.draw()

# Connect the click event to the on_click handler
fig.canvas.mpl_connect('button_press_event', on_click)

# Set up the animation that updates the scatter plot
ani = animation.FuncAnimation(fig, update, interval=100)

try:
    plt.show()
finally:
    ser.close()
