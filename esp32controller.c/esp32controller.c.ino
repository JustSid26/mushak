#include <WiFi.h>
#include <WiFiUdp.h>

// Wi-Fi settings
const char* ssid = "mushak";         
const char* password = "null";  //we’ll decide
const char* roverIP = "192.168.4.2";     // Rover ESP32 IP
const int roverPort = 1234;              // UDP port for communication

WiFiUDP udp;

void setup() {
  Serial.begin(115200); // this number will change on experimentation
  WiFi.begin(ssid, password);

  // checking the connectioin
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }// we dont really need this, we can discuss
  Serial.println("Connected to WiFi");
}

void loop() {
  String command = "";

 
  if (analogRead(34) > 2000) command = “FORWARD"; /*this is not the actual logic, it is just to show that how the connection will look*/
  else if (analogRead(34) < 1000) command = "BACKWARD";
  else if (analogRead(35) > 2000) command = "LEFT";
  else if (analogRead(35) < 1000) command = "RIGHT";
  else command = "STOP";

  // sneding commancd
  udp.beginPacket(roverIP, roverPort);
  udp.print(command);
  udp.endPacket();

  delay(100);  // Adjust the interval based on your needs
}
