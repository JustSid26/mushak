#include <WiFi.h>

// Server ESP32 details
const char* ssid = "ESP32_Server";     // Server Wi-Fi name
const char* password = "12345678";     // Server Wi-Fi password
const char* serverIP = "192.168.4.1";  // Default IP of the server ESP32 in AP mode
const uint16_t serverPort = 80;        // Server port

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Connect to the server's Wi-Fi
  Serial.println("Connecting to server Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to Wi-Fi!");
  Serial.print("Client IP Address: ");
  Serial.println(WiFi.localIP());

  // Connect to the server
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to ESP32 Server!");
    client.println("Hello from ESP32 Client!");
  } else {
    Serial.println("Failed to connect to ESP32 Server");
  }
}

void loop() {
  // Check for server response
  if (client.available()) {
    String response = client.readStringUntil('\n');
    Serial.println("Server response: " + response);
  }

  delay(1000); // Avoid flooding the server
}