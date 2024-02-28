#include "note_sensor.h"
#include <Arduino.h>

#define IR_SENSOR 55
/* HIGH = ei havaintoa, LOW = havainto saatu */

bool isNoteDetected(){
  int sensorValue = digitalRead(IR_SENSOR);

	if(sensorValue == HIGH)
	{
		return false;
	}
	else
	{
		return true;
	}
}
