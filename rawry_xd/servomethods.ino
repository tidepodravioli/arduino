const int inchlength = 10;

void mov(direc dir)
{
  switch(dir){
    case INCH:
      Lservo.write(40);
      Rservo.write(140);
    break;

    case STRAIGHT:
      Lservo.write(40);
      Rservo.write(140);
    break;

    case LEFT:
      Lservo.write(140);
      Rservo.write(140);
      delay(10);
      Lservo.write(90);
      Rservo.write(90);
    break;

    case RIGHT:
      Lservo.write(40);
      Rservo.write(40);
      delay(10);
      Lservo.write(90);
      Rservo.write(90);
    break;
  }
}

bool decision()
{
  mov(INCH);
  if(mes() == empty) return false;
  else return true;
}

bool win()
{
  return false;
}

int mes()
{
  int raw[5];
  int result = 0;
  
  raw[0] = analogRead(A1);
  raw[1] = analogRead(A2);
  raw[2] = analogRead(A3);
  raw[3] = analogRead(A4);
  raw[4] = analogRead(A5);

  const int threshhold = 800;
  if(raw[0] < threshhold) result += B10000;
  if(raw[1] < threshhold) result += B01000;
  if(raw[2] < threshhold) result += B00100;
  if(raw[3] < threshhold) result += B00010;
  if(raw[4] < threshhold) result += B00001;

  /*String printsen = "";
  for(int cur = 0; cur <= 4; cur++){
    if(raw[cur] < 600){
      printsen = printsen + "⏺  ";
    }
    else{
      printsen = printsen + "◯  ";
    }
  }*/
  return result;
}

char * int2bin(unsigned int x)
{
 static char buffer[6];
 for (int i=0; i<6; i++) buffer[4-i] = '0' + ((x & (1 << i)) > 0);
 buffer[5] ='\0';
 return buffer;
}
