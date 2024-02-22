#include <stdio.h>
#include <Arduino.h>
#include "Timer.h"
#include "lcd_screen.h"
#include <Wire.h>
#include "rgb_lcd.h"

/*

  lcd->setText("Hello", 0);
  lcd->setText("World", 1);

*/

Lcd_screen::Lcd_screen(void){
  this->init();  
}

void Lcd_screen::loop(unsigned long currentTime){
  if(disappearTime0>0){
    if(currentTime>disappearTime0){
      this->setText("", 0);
    }
  }
  if(disappearTime1>0){
    if(currentTime>disappearTime1){
      this->setText("", 1);
    }
  }
}

void Lcd_screen::setText(char *text, int row){
  this->setText(text, row, 0, 0);
}

void Lcd_screen::setText(char *text, int row, unsigned long currentTime, unsigned long duration){
  this->lcd.setCursor(0, row);
  this->lcd.print("                ");
  this->lcd.setCursor(0, row);
  this->lcd.print(text);

  if(row==0){
    disappearTime0 = currentTime + duration;
  } else {
    disappearTime1 = currentTime + duration;
  }
}

void Lcd_screen::clear(void){
  this->lcd.clear();
  this->lcd.noBlink();
}

void Lcd_screen::init(void){
  this->lcd.begin(16, 2);
  this->lcd.clear();
  this->lcd.noBlink();
  disappearTime0=0;
  disappearTime1=0; 

  this->setText("     ABLOY", 0, millis(), 3000);
  this->setText("  Aikakapseli", 1, millis(), 3000);
}

