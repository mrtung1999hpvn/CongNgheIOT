#include <Wire.h>
#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
String ThaoTac="";
//our L298N control pins
const int LeftMotorForward = 7; // -> INPUT 1
const int LeftMotorBackward = 6;  // -> INPUT 2
const int RightMotorForward = 5; // -> INPUT 3
const int RightMotorBackward = 4; // -> INPUT 4



#define trig_pin A2 //analog input 1

#define echo_pin A1
//analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name
//
#define Chan2 2
#define Chan3 3
#define Chan9 9

//
void setup(){
  c.reserve(1000);
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);
  pinMode(Chan3, INPUT);
  pinMode(Chan9, INPUT);
  pinMode(Chan2, INPUT);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}


void loop(){
/*
//#define Chan2 2 <- D2
//#define Chan3 3 <- D3
//#define Chan9 9 <- D4
    */
    //moveForward();
    if(ThaoTac=="down")
    {
      Serial.print("DOWN\n");
      moveBackward();
    }
    if(ThaoTac=="up")
    {
      Serial.print("UP\n");
      moveForward();
    }
    if(ThaoTac=="left")
    {
      Serial.print("LEFT\n");
      turnLeft();
    }
    if(ThaoTac=="right")
    {
      Serial.print("RIGHT\n");
      turnRight();
    }
    if(ThaoTac=="auto")
    {
      Serial.print(c);
      Serial.print("AUTO\n");
      moveAuto();
    }
    if(ThaoTac=="servoleft")
    {
      Serial.print("servoleft\n");
      lookLeft();
    }
    if(ThaoTac=="servoright")
    {
      //Serial.print("servoright\n");
      lookRight();
    }
    delay(500);
}
int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}
void moveAuto(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}
int readPing(){ // check khoang cach
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;//250cm
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward(){ // moveBackward

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveForward(){ // Tien moveForward

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}
//
// TRAI LEN 
//  digitalWrite(LeftMotorForward, HIGH);
//  digitalWrite(LeftMotorBackward, HIGH);
//
//TRAI
//
void SpinLeft(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void SpinRight(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);  
}
void turnRight(){
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  delay(500);
}

void turnLeft(){
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  delay(500);
}
// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (0 < Wire.available()) {
    char _c = Wire.read();      /* receive byte as a character */
    ThaoTac  = String(ThaoTac + _c);
  }
}

// function that executes whenever data is requested from master
void requestEvent() {
  Wire.write("Hello Master");  /*send string on request */
}
 
