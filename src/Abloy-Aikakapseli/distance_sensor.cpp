#include "distance_sensor.h"
#include <Arduino.h>

#define PIR_MOTION_SENSOR 14
/* HIGH = lähellä, LOW = kaukana */
bool isCustomerNear = false;

bool isCustomerDetected(){
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);

	if(sensorValue == HIGH)//if the sensor value is HIGH?
	{
		return true;//yes,return ture
	}
	else
	{
		return false;//no,return false
	}
}