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

  
  return result;
}

String int2dots(int results){
  String printsen = "";
  for(int cur = 4; cur >= 0; cur--){
    if(((results >> cur) & 1) == 1){
      printsen = printsen + "⏺  ";
    }
    else{
      printsen = printsen + "◯  ";
    }
  }

  return printsen;
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

char * int2bin(unsigned int x)
{
 static char buffer[6];
 for (int i=0; i<6; i++) buffer[4-i] = '0' + ((x & (1 << i)) > 0);
 buffer[5] ='\0';
 return buffer;
}
