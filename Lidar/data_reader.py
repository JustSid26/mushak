import serial
import struct
import math

# Configure the serial connection
port = '/dev/ttyUSB0'  # Adjust based on your system
baud_rate = 115200  # Default baud rate for YDLIDAR X2
ser = serial.Serial(port, baud_rate, timeout=1)


def parse_lidar_data(data):
    """
    Parses raw data from YDLIDAR X2.
    Each valid frame contains angle (float) and distance (float).
    """
    points = []
    try:
        num_points = len(data) // 6  # Each reading has 2 bytes (angle) + 2 bytes (distance)
        for i in range(num_points):
            # Unpack angle (uint16) and distance (uint16)
            angle, distance = struct.unpack('<HH', data[i * 4:(i + 1) * 4])
            angle = angle / 64.0  # Convert to degrees (as per YDLIDAR protocol)
            distance = distance / 1000.0  # Convert mm to meters

            points.append((angle, distance))
    except Exception as e:
        print(f"Error parsing LiDAR data: {e}")

    return points


try:
    print("Reading LiDAR data...")
    while True:
        if ser.in_waiting > 0:
            raw_data = ser.read(90)  # Adjust buffer size based on expected packet size
            points = parse_lidar_data(raw_data)

            print("Angle (°)  | Distance (m)")
            print("-------------------------")
            for angle, distance in points:
                print(f"{angle:.2f}°  | {distance:.3f} m")
except KeyboardInterrupt:
    print("Exiting...")
finally:
    ser.close()
