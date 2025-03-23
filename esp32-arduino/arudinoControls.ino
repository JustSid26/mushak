#include <Servo.h>
Servo myservo;

int speed = 128;

int pos = 0;

#define dirLeft1 47
#define pwmLeft1 49
#define dirRight1 51
#define pwmRight1 53

#define dirLeft2 46
#define pwmLeft2 48
#define dirRight2 50
#define pwmRight2 52

#define dirLeft3 33 //27
#define pwmLeft3 31 // 
#define dirRight3 29
#define pwmRight3 27


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


  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  speed = 128;
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

  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, speed);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, speed);
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

  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, speed);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, speed);
}

void turn_right() {
  Serial.println("TURNING RIGHT IN PLACE");
  digitalWrite(dirLeft1, HIGH);
  analogWrite(pwmLeft1, 180);
  digitalWrite(dirRight1, LOW);
  analogWrite(pwmRight1, 180);

  digitalWrite(dirLeft2, HIGH);
  analogWrite(pwmLeft2, 180);
  digitalWrite(dirRight2, LOW);
  analogWrite(pwmRight2, 180);

  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, 180);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 180);
}

void turn_left() {
  Serial.println("TURNING left IN PLACE");

  digitalWrite(dirLeft1, LOW);
  analogWrite(pwmLeft1, 180);
  digitalWrite(dirRight1, HIGH);
  analogWrite(pwmRight1, 180);

  digitalWrite(dirLeft2, LOW);
  analogWrite(pwmLeft2, 180);
  digitalWrite(dirRight2, HIGH);
  analogWrite(pwmRight2, 180);

  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 180);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, 180);
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

  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, speed);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, 0);
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

  digitalWrite(dirLeft3, LOW);
  analogWrite(pwmLeft3, 0);
  digitalWrite(dirRight3, LOW);
  analogWrite(pwmRight3, speed);
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

  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, 0);
  digitalWrite(dirRight3, HIGH);
  analogWrite(pwmRight3, speed);
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

  digitalWrite(dirLeft3, HIGH);
  analogWrite(pwmLeft3, speed);
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

// void leftpump(){
//   Serial.println("LEFT PUMP");
//   analogWrite(pwm7, 255);
// }

// void rightpump(){
//   Serial.println("RIGHT PUMPS");
//   analogWrite(pwm8, 255);
// }

// void pumpstop(){
//   Serial.println("STOP PUMPS");
//   analogWrite(pwm7, 0);
//   analogWrite(pwm8, 0);
// }





 void motionMode(){
  stopmotors();
  for(;;){
    if (Serial2.available() > 0) {  // Check if data is available
    String ch = Serial2.readStringUntil('\n');
    ch.trim();
    if(ch == "L1") speed = 64; //25 percent speed
    if(ch == "R1") speed = 200; //80 percent speed
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
    // if(ch == "L2") leftpump();
    // if(ch == "R2") rightpump();
    // if(ch == "STOP") pumpstop();
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
  Serial.println("Raising arm");
  myservo.write(pos);
  pos+=10;

}

void lowerArm(){
  Serial.println("Lowering arm");
  myservo.write(pos);
  pos-=10;
}
