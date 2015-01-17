#include <Servo.h>

Servo servo;

int frontFace = 85; // The Servo's front facing angle
int rightFace = 40; // The Servo's right facing angle
int leftFace = 130; // The Servo's left facing angle

#define trigPin 3; // Trig Pin (Digital)
#define echoPin 2; // Echo Pin (Digital)

int alertRange = 30; // alert rainge in cm
// #define maximumRange 10000;
// #define minimumRange 0;
long duration, cmFront, cmLeft, cmRight; // Duration used to calculate distance

void setup()
{
  servo.attach(9);
  // Test the servo before begining
  servoTest();
  Serial.begin(9600);
}

void loop()
{
  cycleFront();
  cycleLeft();
  cycleRight();
  Serial.print("Front: ");
  Serial.print(cmFront);
  Serial.print("Left: ");
  Serial.print(cmLeft);
  Serial.print("Right: ");
  Serial.println(cmRight);
}

void servoTest()
{
  servo.write(frontFace);
  delay(1000);
  servo.write(rightFace);
  delay(1000);
  servo.write(frontFace);
  delay(1000);
  servo.write(leftFace);
  delay(1000);
  servo.write(frontFace);
  delay(1000);
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);
}

void cycleFront()
{
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(5);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 cmFront = microsecondsToCentimeters(duration);
}

void cycleLeft()
{
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(5); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 cmLeft = microsecondsToCentimeters(duration);
}

void cycleRight()
{
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(5); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 cmRight = microsecondsToCentimeters(duration);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
