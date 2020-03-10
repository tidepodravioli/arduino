#include <Servo.h>

Servo Lservo;
Servo Rservo;

const int lv = 92;
const int rv = 86;

enum direc{LEFT,LEFTD,RIGHT,INCH,HALFINCH,UTURN};

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
