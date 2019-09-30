#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, A1, A2, A3, A4);

int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

bool btn[2] = {false, false}; //debounce array, run btnde() before check

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("WELCOME TO THE");
  lcd.setCursor(0, 1);
  lcd.print("EZ BAKE OVEN!");
  delay(2000);
  clearRows();

  attachInterrupt(digitalPinToInterrupt(2), bake, RISING);
}

bool baking = false;
int temp = 50;
void loop() {
  if(baking){
    digitalWrite(8, LOW); //turns oven on
    if (readCelcius() >= (temp)) digitalWrite(8, HIGH);

    lcd.setCursor(0,0);
    lcd.print("Oven on.");
    lcd.setCursor(0,1);
    lcd.print(readCelcius());
    lcd.print(" C");
    delay(1000);
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Standby.");
    lcd.setCursor(0, 1);
    lcd.print(readCelcius());
    lcd.print(" C");
    delay(1000);
  }
  
  clearRows();
}

void bake(){
  detachInterrupt(digitalPinToInterrupt(2));
  do{
    lcd.setCursor(0,0);
    lcd.print("Set temperature");
    
    int rd5 = analogRead(A5);
    temp = map(rd5, 10, 920, 25, 190);
    lcd.setCursor(0,1);
    lcd.print(temp);
    lcd.print(" C");
    delay(750);
    clearRows();
  }
  while(digitalRead(2) == LOW);
  baking = true;
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(2), bake, RISING);
}

float readCelcius(){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  return Tc;
}
void clearRows(){
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}
