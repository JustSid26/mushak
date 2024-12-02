void setup() {
  Serial.begin(9600); /* we will more likely use this number for connection, but again have to experiemt */
  delay(1000);
}

void loop() {
  Serial.println(“FORWARD”); // sends the commant to arduino
  delay(2000); // Movie forward for 2 seconds

  Serial.println("BACKWARD");
  delay(2000); // Move backward for 2 seconds

  Serial.println("LEFT");
  delay(2000); // Turn left for 2 seconds

  Serial.println("RIGHT");
  delay(2000); // Turn right for 2 seconds

  Serial.println("STOP");
  delay(2000); // Stop for 2 seconds
}
