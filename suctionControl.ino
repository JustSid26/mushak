const int pumpPin = 9; // PWM pin for controlling the pump
int suctionPower = 0;  // Initial suction power (0-255)

void setup() {
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  // Example: Gradually increase suction power
  for (suctionPower = 0; suctionPower <= 255; suctionPower += 10) {
    analogWrite(pumpPin, suctionPower); // Set PWM signal to control pump power
    delay(100); // Wait for 100 ms
  }

  // Example: Gradually decrease suction power
  for (suctionPower = 255; suctionPower >= 0; suctionPower -= 10) {
    analogWrite(pumpPin, suctionPower); // Set PWM signal to control pump power
    delay(100); // Wait for 100 ms
  }
}
