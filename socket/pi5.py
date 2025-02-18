import asyncio
import websockets

# WebSocket server on Pi1
HOST = "0.0.0.0"  # Listen on all interfaces
PORT = 8765  # WebSocket port

async def handler(websocket, path):
    print(f"Client connected: {websocket.remote_address}")
    try:
        async for message in websocket:
            print(f"Received: {message}")
            await websocket.send(f"Echo: {message}")
    except websockets.exceptions.ConnectionClosed:
        print("Client disconnected")

async def main():
    async with websockets.serve(handler, HOST, PORT):
        print(f"WebSocket Server started at ws://{HOST}:{PORT}")
        await asyncio.Future()  # Keep running

if __name__ == "__main__":
    asyncio.run(main())
