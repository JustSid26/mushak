import YdLidarX2 as ydlidar_x2
import socket
import json
import numpy as np
import time

# Lidar setup
port = "/dev/ttyUSB0"
lid = ydlidar_x2.YDLidarX2(port)

# UDP Socket setup
BROADCAST_IP = "10.1.211.179"  # Change if needed
PORT = 5005
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

# Check Lidar connection
if lid.connect():
    print(f"Connected to YDLidarX2 on {port}, broadcasting to {BROADCAST_IP}:{PORT}")
    lid.start_scan()

    while True:
        if lid.available:
            data = lid.get_data()

            # Convert angles (0 to 360 degrees) to radians
            angles = np.radians(np.linspace(0, 360, len(data), endpoint=False))
            distances = np.array(data)

            # Filter invalid distances
            valid = distances > 0
            angles = angles[valid]
            distances = distances[valid]

            # Send data as JSON
            message = json.dumps({"angles": angles.tolist(), "distances": distances.tolist()})
            sock.sendto(message.encode(), (BROADCAST_IP, PORT))

            print("Sent Lidar data:", len(angles), "points")

        time.sleep(0.01)  # 10ms delay for smooth data transmission

else:
    print(f"Failed to connect to YDLidarX2 on port {port}")
