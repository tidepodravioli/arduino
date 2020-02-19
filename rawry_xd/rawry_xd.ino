const int str = B00100;
const int left = B11100;
const int right = B00111;
const int full = B11111;
const int empty = B00000;

enum direc{LEFT,RIGHT,STRAIGHT,INCH,R_INCH};


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  int current = mes();
  
  if(current == left){
    mov(LEFT);
  }
  else if(current == right){
    if(decision()){
      mov(STRAIGHT);
    }
    else{
      mov(RIGHT);
    }
  }
  else if(current == full){
    if(win()){
      
    }
    else{
      mov(R_INCH);
      mov(LEFT);
    }
  }
  else{
    
  }
}
