#include <LiquidCrystal.h>

#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int temperaturePin = 0;

int r = 9;
//I have g at 13 because I just want to make sure that
//the curcuits are wired correctly.
int g = 13;

int b = 10;

float setDegreesF;

float voltage, degreesC, degreesF;

void temp()
{
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;
}

void setup() 
{
  pinMode(r, OUTPUT);
  
  pinMode(g, OUTPUT);
  
  pinMode(b, OUTPUT);
  
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  
  setDegreesF = 77.35;
}
void lcdSetter()
{
  lcd.setCursor(0, 0);
  lcd.print(degreesF);
  lcd.print((char)223);
  lcd.print("F"); 
}
void loop() 
{
  temp();
  lcdSetter();
  alertSwitch();
  delay(1000);
}
float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}
void alertR()
{
  lcd.setCursor(0, 1);
  lcd.write("SO HOT! OUCH!");
  digitalWrite(r, HIGH);
  delay(50);
  digitalWrite(r, LOW);
  delay(50);
}

void alertG()
{
  lcd.setCursor(0, 1);
  lcd.write("Pretty good.");
  digitalWrite(g, HIGH);
  delay(50);
  digitalWrite(g, LOW);
  delay(50);
}

void alertB()
{
  lcd.setCursor(0, 1);
  lcd.write("SO COLD! BRRR!");
  digitalWrite(b, HIGH);
  delay(50);
  digitalWrite(b, LOW);
  delay(50);
}

void alertSwitch() {
  if(degreesF > setDegreesF - 0.5)// - 0.5 is just roughing it out
  {
   alertR(); 
  }
  else if(degreesF < setDegreesF - 0.5)
  {
   alertB(); 
  }
  else
  {
   alertG(); 
  }
}
