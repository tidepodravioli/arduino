



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
  if(mes(20) == empty) return false;
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
