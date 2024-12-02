#include <WiFi.h>
#include <WiFiUdp.h>

// Wi-Fi settings
const char* ssid = "mushak";          
const char* password = “same as above; 
const int localPort = 1234;              

WiFiUDP udp;
char incomingPacket[255];  // buffer for incoming commands

void setup() {
  Serial.begin(115200);  // connection with arduino
  WiFi.begin(ssid, password);

 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  udp.begin(localPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.println(incomingPacket);  // just printing what is about to be sent
  }

  // sending command
  if (Serial.available() > 0) {
    Serial.write(incomingPacket);  //sends the command to arduino
  }
}
