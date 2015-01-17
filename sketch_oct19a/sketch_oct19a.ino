#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int temperaturePin = 0;

int ledPin = 13;

void setup() 
{
  lcd.begin(16, 2);
  
  lcd.print("Temperature:");
  
  Serial.begin(9600);
}

void loop() 
{
  float voltage, degreesC, degreesF, setTemp;
  
  voltage = getVoltage(temperaturePin);

  degreesC = (voltage - 0.5) * 100.0;
  
  degreesF = degreesC * (9.0/5.0) + 32.0;
  
  setTemp = 71.5;
  
  if(degreesF > setTemp)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
   digitalWrite(ledPin, LOW); 
  }
  
  lcd.setCursor(0, 1);
  
  lcd.print(degreesF);
  
  delay(1000);
}
float getVoltage(int pin)
{

  return (analogRead(pin) * 0.004882814);
  
}

