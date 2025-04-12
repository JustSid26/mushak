#include <Servo.h>
Servo myservo;

int speed = 255;

#define dirLeft1 47
#define pwmLeft1 49
#define dirRight1 51
#define pwmRight1 53

#define dirLeft2 46
#define pwmLeft2 48
#define dirRight2 50
#define pwmRight2 52

#define pumpLeft 6  // Example pin for left pump
#define pumpRight 7  // Example pin for right pump


bool motion = true;

void setup() {
  pinMode(dirLeft1, OUTPUT);
  pinMode(pwmLeft1, OUTPUT);
  pinMode(dirRight1, OUTPUT);
  pinMode(pwmRight1, OUTPUT);

  pinMode(dirLeft2, OUTPUT);
  pinMode(pwmLeft2, OUTPUT);
  pinMode(dirRight2, OUTPUT);
  pinMode(pwmRight2, OUTPUT);

  pinMode(pumpLeft, OUTPUT);
  pinMode(pumpRight, OUTPUT);

  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  myservo.attach(9);
  motionMode();
}
void loop(){

}

void backward() {
  Serial.println("MOVING backward");
  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, speed);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, speed);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, speed);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, speed);

}

void forward() {
  Serial.println("MOVING forward");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, speed);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, speed);

  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, speed);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, speed);

}

void turn_right() {
  Serial.println("TURNING RIGHT IN PLACE");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 255);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 255);

  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 255);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 255);

}

void turn_left() {
  Serial.println("TURNING left IN PLACE");

  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 255);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 255);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 255);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 255);

}

void forward_left() {
  Serial.println("MOVING FORWARD LEFT");

  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, speed);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 0);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, speed);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 0);

}

void forward_right() {
  Serial.println("MOVING FORWARD RIGHT");

  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 0);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, speed);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 0);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, speed);
}

void backward_right() {
  Serial.println("MOVING BACKWARD right");
  
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 0);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, speed);

  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 0);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, speed);

}

void backward_left() {
  Serial.println("MOVING BACKWARD left");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, speed);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 0);

  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, speed);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 0);

}

void stopmotors() {
  Serial.println("MOTORS STOP");

  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 0);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 0);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 0);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 0);

}

 void motionMode(){
  stopmotors();
  for(;;){
    if (Serial2.available() > 0) {  // Check if data is available
    String ch = Serial2.readStringUntil('\n');
    ch.trim();
    if(ch == "triangle") pumpMode();
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
    if(ch == "L2") leftpump();
    if(ch == "R2") rightpump();
    if(ch == "STOP") pumpstop();
    if(ch == "FORWARD") raiseArm();
    if(ch == "BACKWARD") lowerArm();
  }
}
}


void leftpump(){
  analogWrite(pumpLeft, 255);
}

void rightpump(){
  analogWrite(pumpRight, 255);
}

void pumpstop() {
  Serial.println("STOPPING PUMPS");
  analogWrite(pumpLeft, 0);
  analogWrite(pumpRight, 0);
}

void raiseArm(){
  Serial.println("Raising arms");
  myservo.write(45);

}

void lowerArm(){
  Serial.println("Lowering arms");
  myservo.write(0);
}
