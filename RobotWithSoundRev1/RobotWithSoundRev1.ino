#include <NewPing.h>

#include <Servo.h>

Servo servo;

#define trigPin 3 // Trig Pin (Digital)
#define echoPin 2 // Echo Pin (Digital)

int alertRange = 30; // alert rainge in cm
// #define maximumRange 10000;
// #define minimumRange 0;
long cmFront, cmLeft, cmRight; // Duration used to calculate distance
int frontFace = 85; // The Servo's front facing angle
int rightFace = 40; // The Servo's right facing angle
int leftFace = 130; // The Servo's left facing angle
void setup()
{
  servo.attach(9);
  // Test the servo before begining
  servoTest();
  Serial.begin(9600);
  NewPing sonar(trigpin, echopin,20000);
}

void loop()
{

  cmFront = cycle(frontFace);
  cmLeft = cycle(leftFace);
  cmRight = cycle(rightFace);

  Serial.print("Front: ");
  Serial.print(cmFront);
  Serial.print("Left: ");
  Serial.print(cmLeft);
  Serial.print("Right: ");
  Serial.println(cmRight);
}

long cycle(int face)
{
  int distance;
  servo.write(face);
  
  distance = sonar.ping_cm();
  return distance;
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
