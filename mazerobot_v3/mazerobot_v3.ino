#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

enum Ttypes{northlL,northlR,northflat,northshort};
enum direc{LEFT,RIGHT};
enum Tblocks{tl,tr,tb}; //short end on left(tl), right (tr), bottom (tb)

Servo Lservo;
Servo Rservo;
bool stopped = false;

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
  txr("(started)");
}

char compass = 'n'; //determines current face
char origins[10]; //stores which direction robot was facing before making decision
int passes[10]; //stores how many times decision was passed
int decision = 0; // stores how many decisions have been made
bool forward = true; //determines if the robot is heading for a intersection or going back
Tblocks tstore; //stores the decision found after following line

void loop() {
  if(stopped == true) reattach();
  
  int x = result();
  txr(x);
  while(followline(x)){
    x = result();
  }
  txr("Decision");
  fullstop();
  Ttypes dec = getType(tstore, compass);
  
  delay(5000);
}

int result(){
  int raw[5];
  raw[0] = analogRead(A1);
  raw[1] = analogRead(A2);
  raw[2] = analogRead(A3);
  raw[3] = analogRead(A4);
  raw[4] = analogRead(A5);
  
  int y = 0;
  for(int pin = 0; pin <= 4; pin++){
    y *= 2;
    if(raw[pin] < 850) y++;
  }

  return y;
}

void txr(String ini){
  ini.toCharArray(information, sizeof(information));
  radio.write(information, sizeof(information));
}
