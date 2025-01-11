void setup() {
  Serial.begin(115200);  // Initialize Serial for debugging
  Serial2.begin(115200);  // Initialize Serial2 for communication with ESP32
}

void loop() {
  if (Serial2.available() > 0) {  // Check if data is available
    String ch = Serial2.readStringUntil('\n');  // Read data until newline
    Serial.println("Received: " + ch);  // Print received data to Serial Monitor
  }
}
