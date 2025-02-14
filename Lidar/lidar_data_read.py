import serial
import math
import struct

# Configure the serial connection
port = 'COM11'  # Adjust this for your system
baud_rate = 115200  # Set to match your LiDAR's baud rate
ser = serial.Serial(port, baud_rate)

def parse_binary_point_cloud(data):
    """
    Parse binary point cloud data. Assuming each point consists of three 32-bit floats (x, y, z).
    """
    points = []
    try:
        num_points = len(data) // 12  # Each point is 12 bytes (3 floats)
        points = [struct.unpack('fff', data[i*12:(i+1)*12]) for i in range(num_points)]
    except Exception as e:
        print(f"Error parsing binary point cloud: {e}")
    return points

def calculate_distances(points):
    """
    Calculate distances for a list of (x, y, z) points.
    """
    distances = [math.sqrt(x**2 + y**2 + z**2) for x, y, z in points]
    return distances

try:
    print("Reading LiDAR data...")
    while True:
        if ser.in_waiting > 0:
            # Read raw byte data from the serial port
            raw_data = ser.readline()
            print(f"Raw byte data: {raw_data}")
            
            # Parse and process the binary point cloud data
            points = parse_binary_point_cloud(raw_data)
            distances = calculate_distances(points)
            
            print("Distances:")
            for i, distance in enumerate(distances):
                print(f"Point {i+1}: {distance:.2f} units")
except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()
