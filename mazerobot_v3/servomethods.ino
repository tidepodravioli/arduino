void swr(int Lser, int Rser){
  txr(compass);
  Lservo.write(Lser);
  Rservo.write(Rser);
}

void fullstop(){
  Lservo.detach();
  Rservo.detach();
  stopped = true;
}

void reattach(){
  Lservo.attach(3);
  Rservo.attach(2);
  stopped = false;
}

void turn(direc way){
  switch(way){
    case LEFT:
      decisions[decision] = compassincr(compass,false);
    case RIGHT:
      decisions[decision] = compassincr(compass,true);
  }
}

void advance(){
  
}
