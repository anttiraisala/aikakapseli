#include <stdio.h>
#include <Arduino.h>
#include "Timer.h"


Timer::Timer(void){
  
}

Timer::Timer(void (*functionPtr)(void)){
  callbackFunc = functionPtr;
}

Timer::Timer(void (*functionPtr)(void), unsigned long currentTime, unsigned long intervalTime){
  callbackFunc = functionPtr;
  
  this->setCurrentTime(currentTime);
  this->setIntervalTime(intervalTime);

  this->calculateNextTriggerTime();
}


void Timer::setCurrentTime(unsigned long currentTime){
  this->currentTime = currentTime;
}

void Timer::setIntervalTime(unsigned long intervalTime){
  this->intervalTime = intervalTime;
}

void Timer::calculateNextTriggerTime(){
  while(this->nextTriggerTime <= this->currentTime){
    this->nextTriggerTime += this->intervalTime ;
  }
}

void Timer::loop(unsigned long currentTime){
  this->currentTime = currentTime;
 
  if(this->currentTime < this->nextTriggerTime){
    return;
  }
  
  this->calculateNextTriggerTime();

  callbackFunc();
}
