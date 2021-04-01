#include "Valve1.h"
#include "Arduino.h"
/*------------------------
ServoConfig for Valve1 with MGR 996R
https://www.towerpro.com.tw/product/mg996r/

Further improvement: 
 * Attach an amp-meter between the sensor and the driver, 
 * if load increases over 1 Amper (read spec sheet), apply fallback strategy, because valve is blocked.
 * Fallback strategy example: try to switch to other position, if doesn't happen within 1 second, shutdown valve and beep/flash, etc. and set valve offline.

------------------------*/
#define CLOSED_POSITION  380 
#define OPEN_POSITION  448 

#define SERVO_FREQ 50
#define INIT_DELAY 300

Valve1::Valve1(int channel, int openPosition, int closedPosition)
{ 
  _driver = Adafruit_PWMServoDriver();
  _channel = channel;
  _isOpen = false;
  _openPosition = openPosition;
  _closedPosition = closedPosition;

}

void Valve1::begin(){
   _driver.begin();
  _driver.setPWMFreq(SERVO_FREQ);
  _driver.setOscillatorFrequency(27000000);
  delay(INIT_DELAY);
  open();
  delay(INIT_DELAY);
  close();
}

void Valve1::open(){
  _driver.setPWM(_channel, 0, OPEN_POSITION);
  _isOpen = true;
}

void Valve1::close(){
  _driver.setPWM(_channel, 0, CLOSED_POSITION);
  _isOpen = false;
}

bool Valve1::isOpen(){
  return _isOpen;
}

int Valve1::getOpenPosition(){
  return _openPosition;
}

int Valve1::getClosedPosition(){
  return _closedPosition;
}
