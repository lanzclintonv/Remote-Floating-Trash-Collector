#include <SoftwareSerial.h>
const int latchPin = 5; //pin 12 on the 595 
const int dataPin = 6; //pin 14 on the 595 
const int clockPin = 4; //pin 11 on the 595 

const int pb1 = 9;
const int pb2 = 10;
const int pb3 = 11;
const int pb4 = 12;

String input = "";
int num = 0;
int op = 0;
SoftwareSerial HC12(2, 3);
void setup() {
  Serial.begin(9600);
  HC12.begin(9600); 
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(pb1, INPUT_PULLUP);  
  pinMode(pb2, INPUT_PULLUP);
  pinMode(pb3, INPUT_PULLUP);
  pinMode(pb4, INPUT_PULLUP);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

  showZero();
}

void loop() {
  if (HC12.available() > 0) {
    input = HC12.readStringUntil('\r\n');
    num = input.toInt();

    if(num == 0){
      showZero();
    }
    else if(num == 1){
      showOne();
    }
    else if(num == 2){
      showTwo();
    }
    else if(num == 3){
      showThree();
    }
    else if(num == 4){
      showFour();
    }
    else if(num == 5){
      showFive();
    }
  }
  if(!digitalRead(pb1) && digitalRead(pb2)){ //Left
    op = 30;
  }
  if(!digitalRead(pb2) && digitalRead(pb1)){ //Right
    op = 40;
  }
  if(!digitalRead(pb1) && !digitalRead(pb2)){ //Forward
    op = 20;
  }
  if(digitalRead(pb1) && digitalRead(pb2)){ //Stop
    op = 10;
  }
  if(!digitalRead(pb3) && digitalRead(pb4)){ //Load
    op = op + 2;
  }
  if(!digitalRead(pb4) && digitalRead(pb3)){ //Unload
    op = op + 3;
  }
  if(digitalRead(pb3) && digitalRead(pb4)){ //Idle
    op = op + 1;
  }
  HC12.println(op);
  delay(100);
}

void showZero(){
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 64); 
  digitalWrite(latchPin, HIGH); 
}

void showOne(){
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 121); 
  digitalWrite(latchPin, HIGH);
}

void showTwo(){
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 36); 
  digitalWrite(latchPin, HIGH);
}

void showThree(){
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 48); 
  digitalWrite(latchPin, HIGH); 
}

void showFour(){
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 25); 
  digitalWrite(latchPin, HIGH); 
}

void showFive(){
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, 18); 
  digitalWrite(latchPin, HIGH); 
}
