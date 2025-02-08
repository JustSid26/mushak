#include <Servo.h>
Servo myservo;
Servo myservo1;

int currentMode = 1;

int pos = 0;
const int pwm1 = 49;   // Motor 1 PWM
const int dir1 = 47;   // Motor 1 DIR
const int pwm2 = 53;  // Motor 2 PWM
const int dir2 = 51;  // Motor 2 DIR

// Motor Driver 2 Pins
const int pwm3 = 41;   // Motor 3 PWM
const int dir3 = 43;   // Motor 3 DIR
const int pwm4 = 37;   // Motor 4 PWM
const int dir4 = 39;   // Motor 4 DIR

const int pwm5 = 29;   // Motor 5 PWM
const int dir5 = 31;   // Motor 5 DIR
const int pwm6 = 25;   // Motor 6 PWM
const int dir6 = 27;   // Motor 6 DIR

const int pwm7 = 52; //for pump1
const int pwm8 = 50;//for pump2

bool motion = true;

// const int dirT = ;
// const int pwmT = ;



void setup() {
  Serial.begin(115200);  // Initialize Serial for debugging
  Serial2.begin(115200);
  myservo.attach(9);
  myservo1.attach(10);
  motionMode();   // Initialize Serial2 for communication with ESP32
}

void loop() {
    if (Serial2.available() > 0) {  // Check if data is available
    String ch = Serial2.readStringUntil('\n');
    ch.trim();
    if(ch == "triangle"){
      toggleMode();
    }if(ch == "L1"){
      MLmode();
    }
  }

}

void toggleMode() {  // Toggle mode
  if (currentMode == 0) {
    Serial.println("Mode: Motion Mode");
    currentMode = 1;
    motionMode();
    delay(500);
  } else {
    Serial.println("Mode: Pump Mode");
    currentMode = 0;
    pumpMode();
    delay(500);
  }
}



void forward(){
  Serial.println("MOVING FORWARD");
      digitalWrite(dir1, HIGH); // Forward direction
      analogWrite(pwm1, 255);
    

    // Control Motor 2
      digitalWrite(dir2, LOW); // Forward direction
      analogWrite(pwm2, 255);

      digitalWrite(dir3, HIGH); // Forward direction
      analogWrite(pwm3, 255);

      digitalWrite(dir4, HIGH); // Forward direction
      analogWrite(pwm4, 255);

      digitalWrite(dir5, HIGH); // Forward direction
      analogWrite(pwm5, 255);

      digitalWrite(dir6, HIGH); // Forward direction
      analogWrite(pwm6, 255);
}

void backward(){
  Serial.println("MOVING BACKWARD");
      digitalWrite(dir1, LOW); // Forward direction
      analogWrite(pwm1, 200200);
    

    // Control Motor 2
      digitalWrite(dir2, LOW); // Forward direction
      analogWrite(pwm2, 200);

      digitalWrite(dir3, LOW); // Forward direction
      analogWrite(pwm3, 200);

      digitalWrite(dir4, LOW); // Forward direction
      analogWrite(pwm4, 200);

      digitalWrite(dir5, LOW); // Forward direction
      analogWrite(pwm5, 200);

      digitalWrite(dir6, LOW); // Forward direction
      analogWrite(pwm6, 200);
}

void forward_left(){
  Serial.println("MOVING FORWARD LEFT");
  digitalWrite(dir1, HIGH); // Forward direction
  analogWrite(pwm1, 255);

  digitalWrite(dir2, LOW); // Forward direction
  analogWrite(pwm2, 0);

  digitalWrite(dir3, HIGH); // Forward direction
  analogWrite(pwm3, 255);

  digitalWrite(dir4, LOW); // Forward direction
  analogWrite(pwm4, 0);

  digitalWrite(dir5, HIGH); // Forward direction
  analogWrite(pwm5, 255);

  digitalWrite(dir6, LOW); // Forward direction
  analogWrite(pwm6, 0);
}

void forward_right(){
  Serial.println("MOVING FORWARD RIGHT");
  digitalWrite(dir1, LOW); // Forward direction
  analogWrite(pwm1, 0);

  digitalWrite(dir2, HIGH); // Forward direction
  analogWrite(pwm2, 255);

  digitalWrite(dir3, LOW); // Forward direction
  analogWrite(pwm3, 0);

  digitalWrite(dir4, HIGH); // Forward direction
  analogWrite(pwm4, 255);

  digitalWrite(dir5, LOW); // Forward direction
  analogWrite(pwm5, 0);

  digitalWrite(dir6, HIGH); // Forward direction
  analogWrite(pwm6, 255);
}

void backward_left(){
  Serial.println("MOVING BACKWARD LEFT");
  digitalWrite(dir1, LOW); // Backward direction
  analogWrite(pwm1, 200);

  digitalWrite(dir2, LOW); // Backward direction
  analogWrite(pwm2, 0);

  digitalWrite(dir3, LOW); // Backward direction
  analogWrite(pwm3, 200);

  digitalWrite(dir4, LOW); // Backward direction
  analogWrite(pwm4, 0);

  digitalWrite(dir5, LOW); // Backward direction
  analogWrite(pwm5, 200);

  digitalWrite(dir6, LOW); // Backward direction
  analogWrite(pwm6, 0);
}

void backward_right(){
  Serial.println("MOVING BACKWARD RIGHT");
  digitalWrite(dir1, LOW); // Backward direction
  analogWrite(pwm1, 0);

  digitalWrite(dir2, LOW); // Backward direction
  analogWrite(pwm2, 200);

  digitalWrite(dir3, LOW); // Backward direction
  analogWrite(pwm3, 0);

  digitalWrite(dir4, LOW); // Backward direction
  analogWrite(pwm4, 200);

  digitalWrite(dir5, LOW); // Backward direction
  analogWrite(pwm5, 0);

  digitalWrite(dir6, LOW); // Backward direction
  analogWrite(pwm6, 200);
}

void turn_left(){
  Serial.println("TURNING LEFT IN PLACE");
  digitalWrite(dir1, HIGH); // Forward direction
  analogWrite(pwm1, 255);

  digitalWrite(dir2, LOW); // Backward direction
  analogWrite(pwm2, 255);

  digitalWrite(dir3, HIGH); // Forward direction
  analogWrite(pwm3, 255);

  digitalWrite(dir4, LOW); // Backward direction
  analogWrite(pwm4, 255);

  digitalWrite(dir5, HIGH); // Forward direction
  analogWrite(pwm5, 255);

  digitalWrite(dir6, LOW); // Backward direction
  analogWrite(pwm6, 255);
}

void turn_right(){
  Serial.println("TURNING RIGHT IN PLACE");
  digitalWrite(dir1, LOW); // Backward direction
  analogWrite(pwm1, 255);

  digitalWrite(dir2, HIGH); // Forward direction
  analogWrite(pwm2, 255);

  digitalWrite(dir3, LOW); // Backward direction
  analogWrite(pwm3, 255);

  digitalWrite(dir4, HIGH); // Forward direction
  analogWrite(pwm4, 255);

  digitalWrite(dir5, LOW); // Backward direction
  analogWrite(pwm5, 255);

  digitalWrite(dir6, HIGH); // Forward direction
  analogWrite(pwm6, 255);
}

void stopmotors(){
      Serial.println("MOTORS STOP");
      digitalWrite(dir1, LOW); // Forward direction
      analogWrite(pwm1, 0);
    

    // Control Motor 2
      digitalWrite(dir2, LOW); // Forward direction
      analogWrite(pwm2, 0);

      digitalWrite(dir3, LOW); // Forward direction
      analogWrite(pwm3, 0);

      digitalWrite(dir4, LOW); // Forward direction
      analogWrite(pwm4, 0);

      digitalWrite(dir5, LOW); // Forward direction
      analogWrite(pwm5, 0);

      digitalWrite(dir6, LOW); // Forward direction
      analogWrite(pwm6, 0);
}
void leftpump(){
  Serial.println("LEFT PUMP");
  analogWrite(pwm7, 255);
}

void rightpump(){
  Serial.println("RIGHT PUMPS");
  analogWrite(pwm8, 255);
}

void pumpstop(){
  Serial.println("STOP PUMPS");
  analogWrite(pwm7, 0);
  analogWrite(pwm8, 0);
}





 void motionMode(){
  for(;;){
    if (Serial2.available() > 0) {  // Check if data is available
    String ch = Serial2.readStringUntil('\n');
    ch.trim();
    if(ch == "triangle") pumpMode();
    if(ch == "circle") break;
    if(ch == "FORWARD") forward();  
    if(ch == "BACKWARD") backward();
    if(ch == "FORWARD_LEFT") forward_left();
    if(ch == "FORWARD_RIGHT") forward_right();
    if(ch == "BACKWARD_LEFT") backward_left();
    if(ch == "BACKWARD_RIGHT") backward_right();
    if(ch == "TURN_LEFT") turn_left();
    if(ch == "TURN_RIGHT") turn_right();
    if(ch == "STOP") stopmotors();
    }
  }
}

void pumpMode(){
  for(;;){
    if (Serial2.available() > 0) {  // Check if data is available
    String ch = Serial2.readStringUntil('\n');
    ch.trim();
    if(ch == "triangle") motionMode();
    if(ch == "circle") break;
    if(ch == "L2") leftpump();
    if(ch == "R2") rightpump();
    if(ch == "STOP") pumpstop();
    if(ch == "FORWARD") raiseArm();
    if(ch == "BACKWARD") lowerArm();
  }
}
}


// void telescopicArm(){
//   for(;;){
//     if (Serial2.available() > 0) {  // Check if data is available
//     String ch = Serial2.readStringUntil('\n');
//     ch.trim();
//     if(ch == "L2") break;
//     if(ch == "FORWARD") forward();  
//     if(ch == "BACKWARD") backward();
//     if(ch == "STOP") stopmotors();
//     }
//   }
// }




void raiseArm(){
  myservo.write(pos);
  myservo1.write(pos);
  pos+=10;

}

void lowerArm(){
  myservo.write(pos);
  myservo1.write(pos);
  pos-=10;
}


void MLmode(){
  
}
