import socket
import time
import numpy as np
import YdLidarX2 as ydlidar_x2
import json

# LiDAR setup
port = '/dev/ttyUSB0'
lid = ydlidar_x2.YDLidarX2(port)

# Socket setup (Broadcast)
BROADCAST_IP = "10.1.211.179"  # Broadcast to all devices in the network
PORT = 5000  # Same port for sender and receiver

# Enable broadcast mode
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

if lid.connect():
    print(f"Connected to YDLidarX2 on port {port}")
    lid.start_scan()

    while True:
        if lid.available:
            data = lid.get_data()
            angles = np.degrees(np.arange(len(data)))  # Convert angles to degrees
            distances = data.tolist()  # Convert NumPy array to list for JSON

            # Pack the data into a JSON object
            payload = json.dumps({"angles": angles.tolist(), "distances": distances})

            # Send to all devices in the network
            sock.sendto(payload.encode(), (BROADCAST_IP, PORT))
            print("Broadcasting:", payload)

        time.sleep(2)  # Send data every 10ms

    lid.stop_scan()
    lid.disconnect()
else:
    print(f"Failed to connect to YDLidarX2 on port {port}")
