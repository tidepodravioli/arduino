#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>

const int straight = B00100;
const int left = B11100;
const int right = B00111;
const int full = B11111;
const int empty = B00000;

enum direc{LEFT,LEFTD,RIGHT,INCH,HALFINCH,UTURN};

Servo Lservo;
Servo Rservo;

RF24 radio(9,10);
char information[128];
String serialQueue = "";
/* I decided to use a serial queue instead of a Serial.print() call to show results all at the same time instead of waiting for each
 *  process to do it's thing. 
 *  
 *  At the end of a loop() iteration, this string is printed as one Serial.println()
 */
int mes(uint8_t iter = 20)
{
  int current = 0;
  const int threshhold = 900;
  
  for(int i = 0; i < iter; i++){
    int result = 0;
    for(int b = 0; b <= 4; b++) if(analogRead(15+b) < threshhold) result |= 1 << (4-b);
    current += result;
  }
  
  current /=  iter;
  return current;
}

void setup() {
  radio.begin();
  radio.setRetries(0, 15);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(17);
  txr("Init started..");
  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Lservo.attach(2);
  Rservo.attach(3);

  Lservo.write(90);
  Rservo.write(90);
  txr("Init finished.");
}

int previous = 0;
void loop() {
   int current;
   current = mes(20);
   serialQueue += (int2dots(current) + "   ");
   serialQueue += (int2bin(current));//sends off the averaged values over to the serial queue
  
  if(current == left){
      serialQueue += ("   LEFT");
      mov(LEFT);
  }
  else if(current == right){
    mov(INCH);
    if(mes(20) == empty){
      serialQueue += ("   RIGHT");
      mov(RIGHT);
    }
    else{
      mov(INCH);
    }
  }
  else if(current == full){
    bool done = false;
    mov(INCH);
    switch(mes(20)){
      case empty:
        mov(LEFTD);
      break;

      case full:
        mov(HALFINCH);
        if(mes(20) == full) done = true;
    }
    if(done){
      Lservo.detach();
      Rservo.detach();
    }
  }
  else if(current == empty){
        serialQueue += ("   UTURN");
        mov(UTURN);
  }
  else{
    serialQueue += ("   STRAIGHT");
    goStraight(current);
  }

  previous = current;
  txr(serialQueue);
  serialQueue = "";
}

void txr(String ini){
  ini.toCharArray(information, sizeof(information));
  radio.write(information, sizeof(information));
}
