const int inchlength = 10;
const int Lval = 80;
const int Rval = 99;

const int turndelay = 600;

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
      Lservo.write(Rval);
      Rservo.write(Lval);
      delay(turndelay);
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


void correct(int comp){
   if(comp == 10000){
      Lservo.write(Lval);
      Rservo.write(Lval);
   }
   else if(comp == B00001){
      Lservo.write(Rval);
      Rservo.write(Rval);
   }
   else if(comp == B01100){
      Lservo.write(Lval);
      Rservo.write(Lval);
   }
   else if(comp == B00110){
      Lservo.write(Rval);
      Rservo.write(Rval);
   }
   else if(comp == B11000){
      Lservo.write(Lval);
      Rservo.write(Lval);
   }
   else if(comp == B00011){
      Lservo.write(Rval);
      Rservo.write(Rval);
   }
   else if(comp == B01000){
      Lservo.write(Lval);
      Rservo.write(Lval);
   }
   else if(comp == B00010){
      Lservo.write(Rval);
      Rservo.write(Rval);
   }
}
