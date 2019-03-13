#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
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

RF24 radio(9,10);
char information[128];

void setup() {

  radio.begin();
  radio.setRetries(0, 15);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openWritingPipe(17);

  Lservo.attach(3);
  Rservo.attach(2);
  Lservo.write(90);
  Rservo.write(90);
  
  DDRC = DDRC | 0x0;
  pinMode(5, INPUT);
  /*
  Serial.println("Waiting for signal");
  while(digitalRead(5) != HIGH);*/
  writeToRadio("Program started.");
}

String decisions = "";
char compass = 'n';
bool backToDecision = false;
bool correction = false;
bool current[5];
int idlecnt = 0;

void loop() {
   measure();
   writeResults();

   
   String comp = result();
   
   if(comp == "00100"){
    advance();
    writeToRadio("STRAIGHT");
   }
   else if(comp == "11100"){
    inch();
    measure();
    if(comp == "00100"){
      //tl case
    }
    else{
      goback();
      delay(100);
      turn(direc::LEFT);
      writeToRadio("LEFT TURN");

      correction = false;
    }
   }
   else if(comp == "00111"){
    inch();
    measure();
    if(comp == "00100"){
      //tl case
    }
    else{
      goback();
      delay(100);
      turn(direc::RIGHT);
      writeToRadio("RIGHT TURN");

      correction = false;
    }
   }
   else if(comp == "00000"){
      swr(140,140);
      delay(700);
   }
   
   else{
    Lservo.write(90);
    Rservo.write(90);

    if(idlecnt > 90) correction = true;
    idlecnt++;
   }
   
   if(correction){
      if(comp == "10000"){
        Lservo.write(40);
        Rservo.write(40);
        delay(200);
     }
     else if(comp == "00001"){
        Lservo.write(140);
        Rservo.write(140);
        delay(200);
     }
     else if(comp == "01100"){
        Lservo.write(40);
        Rservo.write(40);
        delay(100);
     }
     else if(comp == "00110"){
        Lservo.write(140);
        Rservo.write(140);
        delay(100);
     }
     else if(comp == "11000"){
        Lservo.write(40);
        Rservo.write(40);
        delay(90);
     }
     else if(comp == "00011"){
        Lservo.write(140);
        Rservo.write(140);
        delay(90);
     }
     else if(comp == "01000"){
        Lservo.write(40);
        Rservo.write(40);
        delay(90);
     }
     else if(comp == "00010"){
        Lservo.write(140);
        Rservo.write(140);
        delay(90);
     }
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
String result(){
  String ret = "";
  for(int i = 0; i <= 4; i++){
    if(current[i] == true){
      ret += "1";
    }
    else{
      ret += "0";
    }
   }
   return ret;
}
void writeResults(){
  String g = "";
  for(int i = 0; i <= 4; i++){
    if(current[i] == true){
      g+=("1   ");
    }
    else{
      g+=("0   ");
    }
   }
   g+=("\n");
   writeToRadio(g);
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

void writeToRadio(String ini){
  ini.toCharArray(information, sizeof(information));
  radio.write(information, sizeof(information));
}

bool compare(bool * in1, bool * in2){
  if(sizeof(in1) != sizeof(in2)) return false;

  for(int i = 0; i < sizeof(in1); i++){
    if(in1[i] != in2[i]) return false;
  }

  return true;
}
