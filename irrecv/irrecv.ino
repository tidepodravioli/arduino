#include <IRLib2.h>
#include <IRLibAll.h>
#include <IRLibDecodeBase.h>
#include <IRLibGlobals.h>
#include <IRLibRecvBase.h>
#include <IRLibRecvLoop.h>
#include <IRLibSendBase.h>
#include <IRLib_HashRaw.h>

uint16_t data[64];
int datalen = 0;
uint16_t freq = 36;
 
//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(2);
IRsendRaw mySender;
 
//Create a decoder object 
IRdecode myDecoder;   
 
void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Init done."));
}
 
void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    datalen = recvGlobal.recvLength;
    for(bufIndex_t i = 1; i < recvGlobal.recvLength; i++) data[i-1] = recvGlobal.recvBuffer[i];
    for(int i = 0; i < datalen; i++){
      Serial.print(data[i], HEX);
      Serial.print("   ");
    }
    Serial.print('\n');

    myDecoder.decode();
    myDecoder.dumpResults(true);
    Serial.println("Signal recorded.");
  }
  else if(digitalRead(8) == HIGH){
    mySender.send(data, datalen, 40);
    Serial.println("Signal sent.");
    delay(200);
  }

  myReceiver.enableIRIn();
}
