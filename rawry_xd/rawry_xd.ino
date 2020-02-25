#include <Servo.h>

const int straight = B00100;
const int left = B11100;
const int right = B00111;
const int full = B11111;
const int empty = B00000;

enum direc{LEFT,RIGHT,STRAIGHT,INCH,R_INCH};

Servo Lservo;
Servo Rservo;

String serialQueue = "";
void setup() {
  Serial.begin(9600);
  Serial.println("Init started..");
  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Lservo.attach(3);
  Rservo.attach(2);

  Lservo.write(90);
  Rservo.write(90);

  Serial.println("Init finished.");
}

void loop() {
   int current = 0;
   for (int i=0; i < 10; i++) {
   current = current + mes();
   }
   current = current/10;
  serialQueue += (int2bin(current));
  
  if(current == left){
    serialQueue += ("   LEFT");
    mov(LEFT);
  }
  else if(current == right){
    serialQueue += ("   RIGHT");
    mov(RIGHT);
  }
  else if(current == full){
    if(win()){
      
    }
    else{
      mov(INCH);
      mov(LEFT);
    }
  }
  else if(current == straight){
    mov(STRAIGHT);
  }

  Serial.println(serialQueue);
  serialQueue = "";
}
