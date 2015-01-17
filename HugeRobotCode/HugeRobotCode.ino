//********************************************************************************
// * File Name          : Surveillance_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/23
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the surveillance robot.
// ********************************************************************************
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, see http://www.gnu.org/licenses/
/****************************************************************************
  Press the following buttons (SW) to control the robot.
  SW1 forward
  SW3 backward
  SW4 turn right
  SW2 turn left
  SW5 rotate platform clockwise
  SW6 rotate platform counterclockwise
*****************************************************************************/
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
  surveillance.all_stop();        //stop all motors
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
  
  if (cm <
  = alertRange)
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

void remoteStart()
{
  surveillance.remote_setup();    //remote control setup
  delay(500);
}

void remoteControl()
{
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  valuen=surveillance.remote_value_read();  //to read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;    //refresh the previous code    
    if(valueo==SW1)                                 //SW1 action
    {
      surveillance.go_forward(255);                  //go forward    
    }
    else if(valueo==SW3)                            //SW3 action
    {      
      surveillance.go_backward(255);                 //go backward 
    }    
    else if(valueo==SW2)                            //SW2 action
    {    
      surveillance.turn_left(255);                   //turn left          
    }
    else if(valueo==SW4)                            //SW4 action
    {       
      surveillance.turn_right(255);                  //turn right          
    }
    else                                            //if no buttons are pushed
      surveillance.all_stop();                      //stop all motors
  }
}

