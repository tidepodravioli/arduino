void advance(){
  Lservo.write(85);
  Rservo.write(95);
  idlecnt = 0;
}

void goback(){
  Lservo.write(140);
  Rservo.write(40);
}
String makeDecision(Ttypes type){
  
}
void inch(){
  //code for going forward slightly to check for decision
  Lservo.write(70);
  Rservo.write(110);
  delay(150);
}

void turn(direc dir){
  //code for making a turn
  switch(dir){
    case direc::LEFT:
      Lservo.write(40);
      Rservo.write(40);
      delay(359);
      break;
    case direc::RIGHT:
      Lservo.write(140);
      Rservo.write(140);
      delay(355);
      break;
  }
}

void swr(int a, int b){
  Lservo.write(a);
  Rservo.write(b);
}
