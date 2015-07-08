#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_PWMServoDriver.h"

//{motorController.getMotor(1), motorController.getMotor(2), motorController.getMotor(3), motorController.getMotor(4)};

void setup() {
  Serial.begin(115200); //Debug/output serial
  Serial1.begin(115200); //LIDAR serial from Uno
  Adafruit_MotorShield motorController = Adafruit_MotorShield(); //Initialize the shield
  Adafruit_DCMotor *driveMotors[4]; //Create an array of motors (you initialize them as pointers for some reason)
  for(int i = 0; i < 3; i++){
    driveMotors[i] = motorController.getMotor(i+1);
  }
  Serial.println("Brain Arduino Initialized.");
}

void loop() {
  static char buffer[80];
  if (readline(Serial1.read(), buffer, 80) > 0) {
    //... we have gotten data from LIDAR
  }

}

int readline(int readch, char *buffer, int len) // straight from http://hacking.majenko.co.uk/reading-serial-on-the-arduino
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}

