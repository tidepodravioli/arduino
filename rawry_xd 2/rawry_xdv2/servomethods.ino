const int inchdelay = 10;
const int Lval = 92;
const int Rval = 86;

//const int turndelay = 3000;

void mov(direc dir)
{
  switch(dir){
    case LEFT:
      Lservo.write(Lval);
      Rservo.write(Rval);
      delay(10);
      Lservo.write(Lval);
      Rservo.write(Lval);
      while(mes(20) != B00100);
      delay(10);
      Lservo.write(Rval);
      Rservo.write(Rval);
      while(mes(20) != B00100);
    break;

    case LEFTD:
      Lservo.write(Lval);
      Rservo.write(Lval);
      delay(1400);
      Lservo.write(Rval);
      Rservo.write(Rval);
      while(mes(20) != B00100);
    break;

    case RIGHT:
      Lservo.write(Lval);
      Rservo.write(Rval);
      delay(10);
      Lservo.write(Lval);
      Rservo.write(Lval);
      delay(1400);
      Lservo.write(Rval);
      Rservo.write(Rval);
      while(mes(20) != B00100);
    break;
    
    case INCH:
      Lservo.write(Lval);
      Rservo.write(Rval);
      delay(800);
    break;

    case HALFINCH:
      Lservo.write(Lval);
      Rservo.write(Rval);
      delay(400);
    break;
    
    case UTURN:
      Lservo.write(Lval);
      Rservo.write(Lval + 1);
      while(mes(20) != B00100);
      Lservo.write(Rval);
      delay(10);
    break;
  }
}


void goStraight(int comp){
 if(comp == B00100){
    Lservo.write(Lval);
    Rservo.write(Rval);
 }
 else if(comp == B10000){
    Lservo.write(Lval -1);
    Rservo.write(Lval +1);
  }
 else if(comp == B01000){
    Lservo.write(90);
    Rservo.write(Lval +1);
  }
 else if (comp == B00001){
    Lservo.write(Rval +1);
    Rservo.write(Rval -1);
 }
 else if(comp == B00010){
    Lservo.write(Rval -1);
    Rservo.write(90);
 }
}
