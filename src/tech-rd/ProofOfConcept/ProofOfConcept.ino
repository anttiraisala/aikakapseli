/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

/*
Liitettävät komponentit:
- OLED 1.12 inch (SH1107) ( I2C ) ( Tätä ei välttämättä ole valmiissa tuotteessa, mutta kehitysvaiheessa se on kätevä )
- 16x2 LCD (I2C)
- LED Stick D2-D7
- Adjustable PIR Motion Sensor ( A0/14 )
- Infrared Reflective Sensor ( A1/15 )
*/

#include "Ultrasonic.h"
#include "TimerOne.h"

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
    #include <avr/power.h>
#endif


#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
//U8X8_SH1107_SEEED_128X128_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
U8X8_SH1107_SEEED_128X128_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

//U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

#define PIR_MOTION_SENSOR 14

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels0 = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels5 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800);

/*
D2 - D8
A0 is pin 14 
A1 is pin 15
A2 is pin 16
A3 is pin 17
*/

int delayval = 500; // delay for half a second



#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;



unsigned int counter=0;
void blink()
{
    counter++;
}
void timerIsr()
{
    Timer1.detachInterrupt();  //disable the timer1
    Serial.print("IR refl. sens. : ");
    Serial.println(counter,DEC);
    Timer1.attachInterrupt( timerIsr );  //enable the timer1
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(PIR_MOTION_SENSOR, INPUT);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(17, INPUT);

      pixels0.setBrightness(255);
      pixels1.setBrightness(255);
      pixels2.setBrightness(255);
      pixels3.setBrightness(255);
      pixels4.setBrightness(255);
      pixels5.setBrightness(255);
    pixels0.begin(); // This initializes the NeoPixel library.
    pixels1.begin(); // This initializes the NeoPixel library.
    pixels2.begin(); // This initializes the NeoPixel library.
    pixels3.begin(); // This initializes the NeoPixel library.
    pixels4.begin(); // This initializes the NeoPixel library.
    pixels5.begin(); // This initializes the NeoPixel library.

    Serial.begin(9600);
    Serial.println("Start");

    Timer1.initialize();

    Timer1.initialize(1000000); // set a timer of length 1sec
    attachInterrupt(0, blink, RISING);  //INT0
    Timer1.attachInterrupt( timerIsr ); // attach the service routine here
    

   //u8g2.begin();

     u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.clearDisplay();

  // Display initial message
  u8x8.drawString(0, 0, "Hello 2,");
  u8x8.drawString(0, 2, "U8g2!");
  char buf[16];
  ltoa(millis(),buf,10);
  u8x8.drawString(0, 1, buf);
  Serial.print("millis :");
  Serial.println(buf);
  u8x8.drawString(0, 4, "4. rivi");

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Hello, world!");
  lcd.blink();
}

// the loop function runs over and over again forever
void loop() {
  /*
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
*/
    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  pixels0.setPixelColor(0, pixels0.Color(0, 150, 0)); // Moderately bright green color.
  pixels0.setPixelColor(NUMPIXELS-1, pixels0.Color(0, 150, 0)); // Moderately bright green color.
  pixels1.setPixelColor(0, pixels1.Color(150, 150, 0)); // Moderately bright green color.
  pixels1.setPixelColor(NUMPIXELS-1, pixels1.Color(150, 150, 0)); // Moderately bright green color.
  pixels2.setPixelColor(0, pixels2.Color(150, 0, 0)); // Moderately bright green color.
  pixels2.setPixelColor(NUMPIXELS-1, pixels2.Color(150, 0, 0)); // Moderately bright green color.
  pixels3.setPixelColor(0, pixels3.Color(150, 0, 150)); // Moderately bright green color.
  pixels3.setPixelColor(NUMPIXELS-1, pixels3.Color(150, 0, 150)); // Moderately bright green color.
  pixels4.setPixelColor(0, pixels4.Color(0, 0, 150)); // Moderately bright green color.
  pixels4.setPixelColor(NUMPIXELS-1, pixels4.Color(0, 0, 150)); // Moderately bright green color.
  pixels5.setPixelColor(0, pixels5.Color(255, 120, 0)); // Moderately bright green color.
  pixels5.setPixelColor(NUMPIXELS-1, pixels5.Color(255, 120, 0)); // Moderately bright green color.
  for (int i = 1; i < NUMPIXELS-1; i++) {

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels0.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
      pixels1.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
      pixels2.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
      pixels3.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
      pixels4.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
      pixels5.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
  }
      pixels0.show(); // This sends the updated pixel color to the hardware.
      pixels1.show(); // This sends the updated pixel color to the hardware.
      pixels2.show(); // This sends the updated pixel color to the hardware.
      pixels3.show(); // This sends the updated pixel color to the hardware.
      pixels4.show(); // This sends the updated pixel color to the hardware.
      pixels5.show(); // This sends the updated pixel color to the hardware.


  
/*
  int lightSensorValue = analogRead(17);
  Serial.print("light sensor :");//0~400cm
  Serial.println(lightSensorValue);//0~400cm
*/
/*
u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_8x13O_mf);
    u8g2.drawStr(20,44,"Hello Seeed!");
  } while ( u8g2.nextPage() );
*/


  long millisClearDisplayBefore = millis();
  //u8x8.clearDisplay();
  long millisClearDisplayAfter = millis();

  long millisWritingTextBefore = millis();
  // Display initial message
  u8x8.drawString(0, 0, "Hello 2,");
  u8x8.drawString(0, 2, "U8g2!");
  char buf[16];
  ltoa(millis(),buf,10);
  u8x8.drawString(0, 1, buf);
  Serial.print("millis :");
  Serial.println(buf);
  u8x8.drawString(0, 4, "4. rivi");
  long millisWritingTextAfter = millis();

  Serial.print("ClearDisplay millis : ");
  Serial.println(millisClearDisplayAfter-millisClearDisplayBefore, DEC);


  long t1 = millis();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(buf);
  long t2 = millis();
  Serial.print("LCD clear&write millis : ");
  Serial.println(t2-t1, DEC);

  int pirSensorValue = digitalRead(PIR_MOTION_SENSOR);
  Serial.print("PIR sensor value: ");
  if(pirSensorValue == HIGH)
  {
    Serial.println("HIGH");
  } else
  {
    Serial.println("LOW");
  }




  delay(1000);
}
