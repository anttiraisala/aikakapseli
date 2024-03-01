#include <stdio.h>
#include <Arduino.h>
#include "CallbackTimer.h"


CallbackTimer::CallbackTimer(void){
  
}

CallbackTimer::CallbackTimer(void (*functionPtr)(void)){
  callbackFunc = functionPtr;
}

CallbackTimer::CallbackTimer(void (*functionPtr)(void), unsigned long currentTime, unsigned long intervalTime){
  callbackFunc = functionPtr;
  
  this->setCurrentTime(currentTime);
  this->setIntervalTime(intervalTime);

  this->calculateNextTriggerTime();
}


void CallbackTimer::setCurrentTime(unsigned long currentTime){
  this->currentTime = currentTime;
}

void CallbackTimer::setIntervalTime(unsigned long intervalTime){
  this->intervalTime = intervalTime;
}

void CallbackTimer::calculateNextTriggerTime(){
  while(this->nextTriggerTime <= this->currentTime){
    this->nextTriggerTime += this->intervalTime ;
  }
}

void CallbackTimer::loop(unsigned long currentTime){
  this->currentTime = currentTime;
 
  if(this->currentTime < this->nextTriggerTime){
    return;
  }
  
  this->calculateNextTriggerTime();

  callbackFunc();
}
