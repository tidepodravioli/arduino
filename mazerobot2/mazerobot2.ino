const bool straight[] = {false,false,true,false,false};
const bool left[] = {true,true,true,false,false};
const bool right[] = {false,false,true,true,true};
const bool full[] = {true,true,true,true,true};
const bool empty[] = {false,false,false,false,false};

enum Ttypes{northlong,northflat,northshort};
enum direc{LEFT,RIGHT};
enum Tblocks{tl,tr,tt,tb}; //short end on left(tl), right (tr), top (tt), bottom (tb)

void setup() {
  Serial.begin(9600);
  
  DDRC = DDRC | 0x0;
  pinMode(5, INPUT);

  Serial.println("Waiting for signal");
  while(digitalRead(5) != HIGH);
  Serial.println("Program started.");
}

String decisions = "";
char compass = 'n';
bool backToDecision = false;
bool current[] = {false,false,false,false,false};

void loop() {
   measure();

   if(compare(current, straight)){
    advance();
   }
   else if(compare(current,left)){
    inch();
    measure();
    if(compare(current, straight)){
      getType(tl, compass);
      if(decisions != ""){
        decisions[sizeof(decisions)] = 'j';
      }
    }
    
   }
}

void advance(){
  //code for moving forward
}

void inch(){
  //code for going forward slightly to check for decision
}

void turn(direc dir, int angle){
  //code for making a turn
  switch(dir){
    case direc::LEFT:
      compassUpdate(dir, angle);
      break;
  }
}
void measure(){
  for(int pin = 14; pin <= 19; pin++){
    if(analogRead(pin) < 800) current[pin - 14] = true;
    else current[pin - 14] = false;
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

  for(int i = 0; i < sizeof(in1); i++){
    if(in1[i] != in2[i]) return false;
  }

  return true;
}
