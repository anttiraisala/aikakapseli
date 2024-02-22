#include <stdio.h>
#include <Arduino.h>
#include "Timer.h"
#include "lcd_screen.h"
#include <Wire.h>
#include "rgb_lcd.h"

Lcd_screen::Lcd_screen(void){
  
}

void Lcd_screen::init(void){
  this->lcd.begin(16, 2);
  this->lcd.clear();
  this->lcd.noBlink();


  this->lcd.setCursor(0, 0);
  this->lcd.print("     ABLOY");
  
  this->lcd.setCursor(0, 1);
  this->lcd.print("  Aikakapseli");
}

