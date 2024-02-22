#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include "rgb_lcd.h"

class Lcd_screen {

private:

  rgb_lcd lcd;

public:

  Lcd_screen(void);
  void init(void);
    
} ;

#endif // LCD_SCREEN_H