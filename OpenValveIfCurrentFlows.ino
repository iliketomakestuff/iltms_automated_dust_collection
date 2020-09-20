#include "ACS712.h" //https://github.com/RobTillaart/ACS712, also available as Library in Arduino IDE as "ACS712" by Tillaart
#include "Valve1.h"

#define DEBUG false

#define POWER_GRID_FREQ 50 //Hz
#define AMP_SENSOR_PIN A0
#define VALVE1_SERVO_CHANNEL 3

int ampSensorValue= 0;
long loopDelay = DEBUG ? 2000 : 300;

ACS712 ampSensor = ACS712(AMP_SENSOR_PIN);
Valve1 valve1 = Valve1(VALVE1_SERVO_CHANNEL);

void setup() {
  Serial.begin(9600);
  pinMode(AMP_SENSOR_PIN, INPUT);  
  
  if(DEBUG){
    Serial.println("[INFO] DebugMode. LoopDelay increased to 2 seconds");
  }
  
  valve1.begin();
  delay(1000);
}

void loop() {  
  ampSensorValue = ampSensor.mA_AC(POWER_GRID_FREQ);
  
  if(DEBUG){
    Serial.print("[DEBUG] ampSensorValue: ");
    Serial.print(ampSensorValue);
    Serial.print(", valve1: ");
    Serial.println(valve1.isOpen() ? "open" : "closed");
  }

  if(ampSensorValue > 1000 && !valve1.isOpen()){
      Serial.println("[INFO] Opening Valve1 ");
      valve1.open();
  }
  else if(ampSensorValue < 1000 && valve1.isOpen()){
    Serial.println("[INFO] Closing Valve1");
    valve1.close();
  }
    
  delay(loopDelay);
}



