#ifndef CALLBACK_TIMER_H
#define CALLBACK_TIMER_H

class CallbackTimer {

private:

  unsigned long intervalTime=1000;
  unsigned long currentTime=0;
  unsigned long nextTriggerTime=0;

  void (*callbackFunc)(void);

  void calculateNextTriggerTime();


public:

  unsigned long entryTime=0;

  void loop(unsigned long currentTime);
  CallbackTimer(void);
  CallbackTimer(void (*functionPtr)(void));
  CallbackTimer(void (*functionPtr)(void), unsigned long currentTime, unsigned long intervalTime);
  void setIntervalTime(unsigned long intervalTime);
  void setCurrentTime(unsigned long intervalTime);
    
} ;

#endif // CALLBACK_TIMER_H