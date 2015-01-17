/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 2;
int ledPin = 12;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    if(results.value == 2519209162) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW1");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 2999730842) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW2");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 1502638218) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW3");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 2953994586) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW4");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 2368359343) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW5");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 472047109) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW6");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 2054033594) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW7");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    if(results.value == 2534555274) //if the button press equals the hex value 0xC284
    {
        Serial.println("Pushed SW8");
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
    }
    irrecv.resume(); //receive the next value
  }
  delay(100);
}
