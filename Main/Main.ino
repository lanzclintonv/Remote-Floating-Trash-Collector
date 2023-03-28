#include <SoftwareSerial.h>
#include <AFMotor.h>
#include "HX711.h"
#include <Servo.h>

#define DOUT 2
#define CLK 3

AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

SoftwareSerial HC12(10, 11);
Servo myservo;
HX711 scale;
float calibration_factor = 2230;
float units = 00.0;
int weight;

String input = "";
int num = 0;

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  myservo.attach(9);
  
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
  if (HC12.available() > 0) {
    input = HC12.readStringUntil('\r\n');
    num = input.toInt();
    Serial.println(num);
    
    if(num == 11){
      moveStop();
      idle();
    }
    else if(num == 12){
      moveStop();
      load();
    }
    else if(num == 13){
      moveStop();
      unload();
    }
    else if(num == 21){
      moveForward();
      idle();
    }
    else if(num == 22){
      moveForward();
      load();
    }
    else if(num == 23){
      moveForward();
      unload();
    }
    else if(num == 31){
      moveLeft();
      idle();
    }
    else if(num == 32){
      moveLeft();
      load();
    }
    else if(num == 33){
      moveLeft();
      unload();
    }
    else if(num == 41){
      moveRight();
      idle();
    }
    else if(num == 42){
      moveRight();
      load();
    }
    else if(num == 43){
      moveRight();
      unload();
    }
  }
  getWeight();
  HC12.println(weight);
  Serial.println(weight);
  delay(100);
}

void getWeight(){
  units = scale.get_units(), 5;
  if (units < 0)
  {
    units = 0.00;
  }

  if (units >= 0 && units < 1000){
    weight = 0;
  }
  else if(units >= 1000 && units < 2000){
    weight = 1;
  }
  else if(units >= 2000 && units < 3000){
    weight = 2;
  }
  else if(units >= 3000 && units < 4000){
    weight = 3;
  }
  else if(units >= 4000 && units < 5000){
    weight = 4;
  }
  else if(units >= 5000){
    weight = 5;
  }
}

void moveStop(){
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  myservo.write(90);
}
void moveForward(){
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  myservo.write(90);
}

void moveLeft(){
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  myservo.write(45);
}

void moveRight(){
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  myservo.write(135);
}

void load(){
  motor2.run(BACKWARD);
}

void unload(){
  motor2.run(FORWARD);
}

void idle(){
  motor2.run(RELEASE);
}

//  moveStop();
//  idle();
//  for(int i=0; i<7; i++){
//    delay(1000);
//  }
//  moveForward();
//  for(int i=0; i<7; i++){
//    delay(1000);
//  }
//  moveLeft();
//  for(int i=0; i<7; i++){
//    delay(1000);
//  }
//  moveRight();
//  for(int i=0; i<7; i++){
//    delay(1000);
//  }
//  moveForward();
//  load();
//  for(int i=0; i<7; i++){
//    delay(1000);
//  }
//  moveStop();
//  for(int i=0; i<7; i++){
//    delay(1000);
//  }
