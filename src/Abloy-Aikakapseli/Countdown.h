#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include "AikakapseliEeprom.h"

class Countdown {

  private:


  public:

  Countdown(void);

  void init(void);
  void loop(unsigned long currentTime);
  


};

#endif // COUNTDOWN_H