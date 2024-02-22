#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include "rgb_lcd.h"

class Lcd_screen {

private:

  rgb_lcd lcd;

  unsigned long disappearTime0;
  unsigned long disappearTime1; 

public:

  Lcd_screen(void);
  void init(void);
  void clear(void);

  void setText(char *text, int row);
  void setText(char *text, int row, unsigned long currentTime, unsigned long duration);
    
} ;

#endif // LCD_SCREEN_H