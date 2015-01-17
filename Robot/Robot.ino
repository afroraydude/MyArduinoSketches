#include <MakeItRobotics.h> //install library
MakeItRobotics surveillance; //declare object
// **************************************************************************
// *                            Power Up Init.
// **************************************************************************
#define echoPin 9 // Echo Pin
#define trigPin 10 // Trigger Pin

int alertRange = 30; // alert rainge in cm
int maximumRange = 10000; // Maximum range needed in cm
int minimumRange = 0; // Minimum range needed cm
long duration, in, cm, feet, meter; // Duration used to calculate distance

void setup() 
{
  Serial.begin(10420);            //tell the Arduino to communicate with Make: it PCB
  delay(500);                     //delay 500ms
  soundStart();
  surveillance.all_stop();        //stop all motorS
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{  
  //remoteControl();
  /* The following trigPin/echoPin cycle is used to determine the
  distance of the nearest object by bouncing soundwaves off of it. */ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  in = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  feet = in / 12;
  meter = cm / 500;
  
  if (cm <= alertRange)
  {
    surveillance.go_backward(255);
    delay(250);
    surveillance.all_stop();
  }
  else
  {
    surveillance.go_forward(255);
    delay(250);
    surveillance.all_stop();
  }
  
  // Get it done in a half a second
  delay(250);
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)  //interrupt code
{
  surveillance.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}

void soundStart()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
