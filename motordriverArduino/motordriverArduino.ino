
// Motor Driver Pins
#define IN1 16  // Motor 1 forward
#define IN2 17  // Motor 1 backward
#define IN3 18  // Motor 2 forward
#define IN4 19  // Motor 2 backward
#define ENA 5   // Motor 1 speed
#define ENB 21  // Motor 2 speed

void setup() {
  Serial.begin(9600); // connection with esp32

  // Set motor control pins as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stopMotors();
 
}

void loop() {
  // checks for commands
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil(‘\n'); // editing this when signal comes
    command.trim(); //just to be safe, or we can remove if u want

    if (command == "FORWARD") {
      forward();
    } else if (command == "BACKWARD") {
      backward();
    } else if (command == "LEFT") {
      turnLeft();
    } else if (command == "RIGHT") {
      turnRight();
    } else if (command == "STOP") {
      stopMotors();
    }
  }
}

// this is the direction control for now
void forward() {
  analogWrite(ENA, 255); // Full speed for Motor 1
  analogWrite(ENB, 255); // Full speed for Motor 2

  digitalWrite(IN1, HIGH); // Motor 1 forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Motor 2 forward
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, 255); // Full speed for Motor 1
  analogWrite(ENB, 255); // Full speed for Motor 2

  digitalWrite(IN1, LOW); // Motor 1 backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); // Motor 2 backward
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, 255); // Full speed for Motor 1
  analogWrite(ENB, 255); // Full speed for Motor 2

  digitalWrite(IN1, LOW);  // Motor 1 backward
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); // Motor 2 forward
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 255); // Full speed for Motor 1
  analogWrite(ENB, 255); // Full speed for Motor 2

  digitalWrite(IN1, HIGH); // Motor 1 forward
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Motor 2 backward
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0); // Stop Motor 1
  analogWrite(ENB, 0); // Stop Motor 2

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

