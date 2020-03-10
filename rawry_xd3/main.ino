void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Lservo.attach(2);
  Rservo.attach(3);

  Lservo.write(90);
  Rservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*Serial.println(mes());
  swr(lv +1, rv+2);
  while(mes() != B01000);
  swr(lv-2, rv -1);
  while(mes() != B00010);*/

  switch(mes()){
    case B11100:
      mov(LEFT);
    break;

    case B00111:
      mov(RIGHT);
    break;
    
    default:
      followLine(mes());
    break;
  }
}
