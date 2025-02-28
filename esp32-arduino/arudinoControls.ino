#include <Servo.h>
Servo myservo;

int currentMode = 1;

int pos = 0;
#define dirLeft1 51
#define pwmLeft1 53
#define dirRight1 47
#define pwmRight1 49

#define dirLeft2 39
#define pwmLeft2 37
#define dirRight2 43
#define pwmRight2 41

#define dirLeft3 33
#define pwmLeft3 31
#define dirRight3 29
#define pwmRight3 27

#define pwm7 52 // for pump1
#define pwm8 50 // for pump2

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

  pinMode(dirLeft3, OUTPUT);
  pinMode(pwmLeft3, OUTPUT);
  pinMode(dirRight3, OUTPUT);
  pinMode(pwmRight3, OUTPUT);


  pinMode(pwm7, OUTPUT);
  pinMode(pwm8, OUTPUT);

  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  myservo.attach(9);
  myservo1.attach(10);
  motionMode();
}
void loop(){

}

void forward() {
  Serial.println("MOVING FORWARD");
  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 255);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 255);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 255);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 255);

  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 255);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 255);
}

void backward() {
  Serial.println("MOVING BACKWARD");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 255);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 255);
  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 255);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 255);
  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, 255);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, 255);
}

void turn_right() {
  Serial.println("TURNING RIGHT IN PLACE");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 128);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 128);
  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 128);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 128);
  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, 128);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 128);
}

void turn_left() {
  Serial.println("TURNING left IN PLACE");
  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 128);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 128);
  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 128);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 128);
  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 128);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, 128);
}

void forward_left() {
  Serial.println("MOVING FORWARD LEFT");
  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 255);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 0);
  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 255);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 0);
  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 255);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 0);
}

void forward_right() {
  Serial.println("MOVING FORWARD RIGHT");
  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 0);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 255);
  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 0);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 255);
  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 0);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 255);
}

void backward_right() {
  Serial.println("MOVING BACKWARD right");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 0);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 255);
  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 0);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 255);
  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, 0);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, 255);
}

void backward_left() {
  Serial.println("MOVING BACKWARD left");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 255);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 0);
  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 255);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 0);
  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, 255);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, 0);
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
  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 0);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 0);
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
  stopmotors();
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
  Serial.println("Raising lauda");
  myservo.write(pos);
  myservo1.write(pos);
  pos+=10;

}

void lowerArm(){
  Serial.println("Lowering Lauda");
  myservo.write(pos);
  myservo1.write(pos);
  pos-=10;
}

void MLmode(){
  stopmotors();
  for(;;){
    if (Serial3.available() > 0) {  // Check if data is available
    String ch = Serial3.readStringUntil('\n');
    ch.trim();
    if(ch == "option") break;
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
