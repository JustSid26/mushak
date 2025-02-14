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

def filter_points(points, min_distance=0.1, max_distance=5.0):
    """
    Filter out points that are likely noise.
    Adjust min_distance and max_distance based on your environment.
    """
    return [p for p in points if min_distance < p[1] < max_distance]

def smooth_scan(points, window_size=5):
    """
    Apply a moving average filter along the angular dimension.
    The points are sorted by angle, and each point's distance is replaced
    by the average of its neighbors within the window.
    """
    if not points:
        return points
    # Sort points by angle
    points_sorted = sorted(points, key=lambda p: p[0])
    smoothed_points = []
    n = len(points_sorted)
    for i in range(n):
        start = max(0, i - window_size // 2)
        end = min(n, i + window_size // 2 + 1)
        avg_distance = sum(p[1] for p in points_sorted[start:end]) / (end - start)
        angle = points_sorted[i][0]
        x = avg_distance * math.cos(math.radians(angle))
        y = avg_distance * math.sin(math.radians(angle))
        smoothed_points.append((angle, avg_distance, x, y))
    return smoothed_points

# Set up the matplotlib figure and scatter plot
fig, ax = plt.subplots()
scatter = ax.scatter([], [], c='blue', s=10)
ax.set_xlim(-5, 5)
ax.set_ylim(-5, 5)
ax.set_xlabel("X (m)")
ax.set_ylabel("Y (m)")
ax.set_title("YDLIDAR X2 Visualization (Smoothed)")

def update(frame):
    """
    Animation update function that reads from the serial port,
    parses the latest data, applies filtering and smoothing,
    and updates the scatter plot.
    """
    global current_points
    if ser.in_waiting:
        raw_data = ser.read(ser.in_waiting)
        new_points = parse_lidar_data(raw_data)
        if new_points:
            # Accumulate points (or you could replace with new_points for each scan)
            current_points = new_points

    # Filter and smooth the current scan
    filtered_points = filter_points(current_points)
    smoothed_points = smooth_scan(filtered_points, window_size=5)

    # Update scatter plot with smoothed points
    coords = [(p[2], p[3]) for p in smoothed_points]
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

    # Use the smoothed and filtered points for annotation
    filtered_points = filter_points(current_points)
    smoothed_points = smooth_scan(filtered_points, window_size=5)

    min_dist = float('inf')
    closest_point = None
    for p in smoothed_points:
        dx = event.xdata - p[2]
        dy = event.ydata - p[3]
        d = math.sqrt(dx * dx + dy * dy)
        if d < min_dist:
            min_dist = d
            closest_point = p

    # Threshold for selection (0.1 m)
    if min_dist < 0.1 and closest_point is not None:
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

fig.canvas.mpl_connect('button_press_event', on_click)
ani = animation.FuncAnimation(fig, update, interval=100)

try:
    plt.show()
finally:
    ser.close()
