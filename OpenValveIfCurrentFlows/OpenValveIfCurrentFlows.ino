#include "ACS712.h" //https://github.com/RobTillaart/ACS712, also available as Library in Arduino IDE as "ACS712" by Tillaart
#include "Valve1.h"
#include "Arduino_DebugUtils.h"  //Arduino Debug utils, available as library in Arduino IDE

#define DEBUG false
#define POWER_GRID_FREQ 50 //Hz
#define NUM_SENSORS 10


long loopDelay =  300;
long initDelay = 1000;

struct MapEntry {
  int ampSensorChannel;
  int valveServoChannel;
  int openPosition;
  int closedPosition;
};


MapEntry sensorMap[NUM_SENSORS] = {
    //          ampSensorChannel, valveServoChannel,  valveOpenPosition,  valveClosedPosition
    (MapEntry){ A0,               3,                  380,                448                 }
    //(MapEntry){ A1,               3,                  380,                448                 },
    //(MapEntry){ A2,               3,                  380,                448                 }, 
    //(MapEntry){ A3,               3,                  380,                448                 },   
    // Don't use A4 and A5 because they are also connected to SCL and SDA on the servo shield.
    // Don't use A6 and A7 because they are physically not connected
    //(MapEntry){ A8,               3,                  380,                448                 },  
    // ...
    //(MapEntry){ A15,              3,                  380,                448                 },
  };


ACS712* sensors[NUM_SENSORS];
Valve1* valves[NUM_SENSORS];

void setup() {
  Serial.begin(9600);

  if(DEBUG){
    Debug.print(DBG_INFO, "DebugMode. LoopDelay increased to 2 seconds");
    loopDelay = 2000;
    Debug.setDebugLevel(DBG_VERBOSE);

  }

  Debug.print(DBG_INFO, "Initializing");


  for (int i=0;i<NUM_SENSORS; i++) {
    Debug.print(DBG_DEBUG, "Initializing sensor: %d", i);
    pinMode(sensorMap[i].ampSensorChannel, INPUT);
    sensors[i] = new ACS712(sensorMap[i].ampSensorChannel);
    valves[i] = new Valve1(sensorMap[i].valveServoChannel, sensorMap[i].openPosition, sensorMap[i].closedPosition);
    valves[i]->begin();
    delay(initDelay);

  }
}


int ampSensorValue= 0;
void loop() {  
  for (int i=0;i<NUM_SENSORS; i++) {
    ampSensorValue = sensors[i]->mA_AC(POWER_GRID_FREQ);
  
    if(DEBUG){
      Debug.print(DBG_DEBUG, "  #%d ampSensorValue: %f, valve: ", i, ampSensorValue,  valves[i]->isOpen() ? "open" : "closed");
    }
  
    if(ampSensorValue > 1000 && !valves[i]->isOpen()){
        Debug.print(DBG_INFO, "Opening Valve %d", i);
        valves[i]->open();
    }
    
    else if(ampSensorValue < 1000 && valves[i]->isOpen()){
      Debug.print(DBG_INFO, "Closing Valve %d", i);
      valves[i]->close();
    }
    
    delay(loopDelay);
  }
}
