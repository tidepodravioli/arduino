void followLine(int res)
{
  if(res == B00100){
    swr(lv,rv);
  }
  else if (res < B00100){
    swr(lv+1, rv+1);
  }
  else if (res > B00100){
    swr(lv-1, rv-1);
  }
}

void mov(direc dir)
{
  switch(dir){
    case LEFT:
      swr(lv,rv);
      delay(900);
      swr(rv,rv);
      while(mes() != B00100);
      delay(10);
      swr(lv,lv);
      while(mes(20) != B00100);
    break;

    case LEFTD:
    break;

    case RIGHT:
      swr(lv,rv);
      delay(900);
      swr(lv,lv);
      while(mes() != B00100);
      delay(10);
      swr(rv,rv);
      while(mes(20) != B00100);
    break;
    
    case INCH:
    break;

    case HALFINCH:
    break;
    
    case UTURN:
    break;
  }
}

void swr(int lserv, int rserv)
{
  Lservo.write(lserv);
  Rservo.write(rserv);
}
