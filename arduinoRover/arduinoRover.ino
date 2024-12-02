// Motor Driver Pins
#define IN1 2  // Motor 1 forward
#define IN2 3  // Motor 1 backward
#define IN3 4  // Motor 2 forward
#define IN4 5  // Motor 2 backward
#define ENA 6  // Motor 1 speed
#define ENB 7  // Motor 2 speed

void setup() {
  Serial.begin(9600);  // communication with rover ESP32

  // Motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();  // motors are stopped initially
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();  

    if (command == "FORWARD") forward();
    else if (command == "BACKWARD") backward();
    else if (command == "LEFT") turnLeft();
    else if (command == "RIGHT") turnRight();
    else if (command == "STOP") stopMotors();
  }
}
