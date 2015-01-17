/*
 LCD Print
 
 Print the reading from a sensor to the screen.
 
 Circuit:
 * Arduino Robot
 
 created 1 May 2013
 by X. Yang
 modified 12 May 2013
 by D. Cuartielles
 
 This example is in the public domain
 */

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int value;

void setup() {
  // initialize the robot
  Robot.begin();
  // initialize the robot's screen
  Robot.beginTFT();
  Robot.beginSD();
  Robot.drawBMP("lg1.bmp", 0, 0);
}

void loop() {
 
}
