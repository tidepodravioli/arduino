#include <Servo.h>

const bool straight[] = {false,false,true,false,false};
const bool left[] = {true,true,true,false,false};
const bool right[] = {false,false,true,true,true};
const bool full[] = {true,true,true,true,true};
const bool empty[] = {false,false,false,false,false};

enum Ttypes{northlong,northflat,northshort};
enum direc{LEFT,RIGHT};
enum Tblocks{tl,tr,tt,tb}; //short end on left(tl), right (tr), top (tt), bottom (tb)

Servo Lservo;
Servo Rservo;
int Lpos = 0;
int Rpos = 0;

void setup() {
  Serial.begin(9600);

  Lservo.attach(3);
  Rservo.attach(2);
  Lservo.write(90);
  Rservo.write(90);
  
  DDRC = DDRC | 0x0;
  pinMode(5, INPUT);
  /*
  Serial.println("Waiting for signal");
  while(digitalRead(5) != HIGH);*/
  Serial.println("Program started.");
}

String decisions = "";
char compass = 'n';
bool backToDecision = false;
bool current[5];

void loop() {
   measure();

   for(int i = 0; i <= 4; i++){
    if(current[i] == true){
      Serial.print("1   ");
    }
    else{
      Serial.print("0   ");
    }
   }
   Serial.print("\n");

   if(grab(straight)){
    advance();
    Serial.println("STRAIGHT");
   }
   else if(grab(left)){
    inch();
    measure();
    if(grab(straight)){
      //tl case
    }
    else{
      turn(direc::LEFT);
      Serial.println("LEFT TURN");
    }
   }
   else if(grab(right)){
    inch();
    measure();
    if(grab(straight)){
      //tl case
    }
    else{
      turn(direc::RIGHT);
      Serial.println("LEFT TURN");
    }
   }
   else{
    Lservo.write(90);
    Rservo.write(90);
   }
}

void advance(){
  Lservo.write(40);
  Rservo.write(140);
}

void inch(){
  //code for going forward slightly to check for decision
}

void turn(direc dir){
  //code for making a turn
  switch(dir){
    case direc::LEFT:
      Lservo.write(40);
      Rservo.write(140);
      delay(10);
      Lservo.write(90);
      Rservo.write(90);
      break;
    case direc::RIGHT:
      Lservo.write(140);
      Rservo.write(40);
      delay(10);
      Lservo.write(90);
      Rservo.write(90);
      break;
  }
}
void measure(){
  int raw[5];
  raw[0] = analogRead(A1);
  raw[1] = analogRead(A2);
  raw[2] = analogRead(A3);
  raw[3] = analogRead(A4);
  raw[4] = analogRead(A5);
  
  for(int pin = 0; pin <= 4; pin++){
    if(raw[pin] < 800) current[pin] = true;
    else current[pin] = false;
  }
}
void compassUpdate(direc dir, int angle){
  if(dir == direc::LEFT){
    if(angle == 90){
      switch(compass){
        case 'n':
          compass = 'w';
          break;
         case 'w':
          compass = 's';
          break;
         case 's':
          compass = 'e';
          break;
         case 'e':
          compass = 'n';
          break;
      }
    }
    else if(angle == 180){
      switch(compass){
        case 'n':
          compass = 's';
          break;
         case 'w':
          compass = 'e';
          break;
         case 's':
          compass = 'n';
          break;
         case 'e':
          compass = 'w';
          break;
      }
    }
  }
  else if(dir == direc::RIGHT){
    if(angle == 90){
      switch(compass){
        case 'n':
          compass = 'e';
          break;
         case 'w':
          compass = 'n';
          break;
         case 's':
          compass = 'w';
          break;
         case 'e':
          compass = 's';
          break;
      }
    }
    else if(angle == 180){
      switch(compass){
        case 'n':
          compass = 's';
          break;
         case 'w':
          compass = 'e';
          break;
         case 's':
          compass = 'n';
          break;
         case 'e':
          compass = 'w';
          break;
      }
    }
  }
      
}

Ttypes getType(Tblocks in, char compassdir){
  if(compassdir == 'n'){
    if(in == Tblocks::tl || in == Tblocks::tr) return Ttypes::northlong;
    if(in == Tblocks::tb) return Ttypes::northflat;
  }
  else if(compassdir == 'e'){
    if(in == Tblocks::tr) return Ttypes::northflat;
    if(in == Tblocks::tl) return Ttypes::northshort;
  }
  else if(compassdir == 's'){
    if(in == Tblocks::tl || in == Tblocks::tr) return Ttypes::northlong;
    if(in == Tblocks::tb) return Ttypes::northshort;
  }
  else if(compassdir == 'w'){
    if(in == Tblocks::tb) return Ttypes::northlong;
    if(in == Tblocks::tl) return Ttypes::northflat;
    if(in == Tblocks::tr) return Ttypes::northshort;
  }
}
bool compare(bool * in1, bool * in2){
  if(sizeof(in1) != sizeof(in2)) return false;

  for(int i = 0; i <= sizeof(in1); i++){
    if(in1[i] != in2[i]) return false;
  }

  return true;
}

bool grab(bool * comparison){
  int n =5;
  int m =5;
  if (n != m) 
    return false; 
  
    sort(arr1, arr1+n); 
    sort(arr2, arr2+m); 
  
    // Linearly compare elements 
    for (int i=0; i<n; i++) 
         if (arr1[i] != arr2[i]) 
            return false; 
  
    // If all elements were same. 
    return true; 
}

