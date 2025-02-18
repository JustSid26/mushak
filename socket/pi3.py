import asyncio
import websockets
import socket


# Attempt to resolve Pi1's IP (mDNS or default gateway assumption)
def get_pi1_ip():
    try:
        return socket.gethostbyname("raspberrypi.local")  # Try mDNS
    except socket.gaierror:
        return "192.168.4.1"  # Default gateway for Pi1's hotspot


async def connect():
    pi1_ip = get_pi1_ip()
    uri = f"ws://{pi1_ip}:8765"

    async with websockets.connect(uri) as websocket:
        print(f"Connected to {uri}")
        await websocket.send("Hello from Pi2!")
        response = await websocket.recv()
        print(f"Response from server: {response}")


if __name__ == "__main__":
    asyncio.run(connect())
