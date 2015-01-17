/* NewPingRunawayRobot.cpp - Created by Rashaad Thomas

  This program is purposed for the Official Arduino Robot under 2 ATmega32u4 
  microcontrollers. This program uses 25,092 bytes (87%) of program storage space. Maximum 
  is 28,672 bytes. Global variables use 1,821 bytes (71%) of dynamic memory, leaving 739 
  bytes for local variables. Maximum is 2,560 bytes. This program uses an ultrasonic 
  distance sensor, it's capable of detecting and avoiding obstacles like walls.
  
  Circuit is as follows:
  * Arduino Robot
  * Parallax Ping))) Ultrasonic Sensor connected to TKD3 pin, displayed as D3 on Control 
  Board.  
 
  This program requires ArduinoRobot.h, Wire.h, SPI.h, and NewPing.h, along with their
  respective C++ files.
  
  Please note: An Arduino Uno (Rev 3) was used as an ISP, or In-System Programmer, to bypass 
  the Arduino Bootloader on the microcontroller (see image A).  
 
*/

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>
#include <NewPing.h>

#define TRIGGER_PIN  TKD3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     TKD3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 2000 // Maximum distance we want to ping for (in centimeters).

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  // initialize the Robot, SD card, and display
  Serial.begin(9600);
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSD();
  Robot.displayLogos();

  // draw a face on the LCD screen
  setFace(true);
}

void loop() {
  // If the robot is blocked, turn until free
  while (getDistance() < 40) { // If an obstacle is less than 20cm away
    setFace(false); //shows an unhappy face
    Robot.motorsStop(); // stop the motors
    delay(1000); // wait for a moment
    Robot.turn(90); // turn to the right and try again
    setFace(true); // happy face
  }
  // if there are no objects in the way, keep moving
  Robot.motorsWrite(255, 255);
  delay(100);
}

// return the distance in cm
float getDistance() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  // read the value from the sensor
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //Convert the sensor input to cm.
  unsigned int distance_cm = uS / US_ROUNDTRIP_CM;
  return distance_cm;
}

// make a happy or sad face
void setFace(boolean onOff) {
  if (onOff) {
    // if true show a happy face
    Robot.background(0, 0, 255);
    Robot.setCursor(44, 60);
    Robot.stroke(0, 255, 0);
    Robot.setTextSize(4);
    Robot.print(":)");
  } else {
    // if false show an upset face
    Robot.background(255, 0, 0);
    Robot.setCursor(44, 60);
    Robot.stroke(0, 255, 0);
    Robot.setTextSize(4);
    Robot.print("X(");
  }
}
