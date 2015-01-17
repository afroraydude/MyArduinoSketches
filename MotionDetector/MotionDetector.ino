/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v 
 GND to arduino GND
 Echo to Arduino pin 7 
 Trig to Arduino pin 8
 
 This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
 Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
 And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
 on 10 Nov 2012.
 */


#define echoPin 2 // Echo Pin
#define trigPin 3 // Trigger Pin
#define piezoPin 9 // Onboard LED

int alertRange = 30; // alert rainge in cm
int maximumRange = 10000; // Maximum range needed in cm
int minimumRange = 0; // Minimum range needed cm
long duration, in, cm, feet, meter; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(piezoPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(2); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 in = microsecondsToInches(duration);
 cm = microsecondsToCentimeters(duration);
 feet = in / 12;
 meter = cm / 1000;
 
 if (cm >= maximumRange)
 {
 Serial.println("OUT OF RANGE!");
 }
 else
 {
  Serial.print(meter);
  Serial.print("m, ");
  Serial.print(feet);
  Serial.print("ft, ");
  Serial.print(in);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 }
 
 if(cm <= alertRange)
 {
  tone(piezoPin, 500);
 }
 else
 {
  noTone(piezoPin); 
 }
 
 //Delay 50ms before next reading.
 delay(1000);
}
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


