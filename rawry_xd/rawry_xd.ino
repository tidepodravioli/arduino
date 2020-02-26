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
/* I decided to use a serial queue instead of a Serial.print() call to show results all at the same time instead of waiting for each
 *  process to do it's thing. 
 *  
 *  At the end of the loop() iteration, this string is printed as one Serial.println()
 */
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
   int current = 0; //creates a variable that holds the current averaged value
   for (int i=0; i < 10; i++) current = current + mes(); //collects and adds up 10 iterations of the sensor value
   current = current/10; //averages the collected values
   serialQueue += (int2dots(current) + "   ");
   serialQueue += (int2bin(current));//sends off the averaged values over to the serial queue
  
  if(current == left){
    serialQueue += ("   LEFT");
    mov(LEFT);
  }
  else if(current == right){
    serialQueue += ("   RIGHT");
    mov(RIGHT);
  }
  else if(current == full){
    mov(INCH);
    mov(LEFT);
  }
  else if(current == straight){
    mov(STRAIGHT);
  }
  else{
    correct(current);
  }

  Serial.println(serialQueue);
  serialQueue = "";
}
