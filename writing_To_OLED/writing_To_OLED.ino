#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

#define SCANDELAY 250

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define XPOS 0
#define YPOS 1
#define DELTAY 2




RTC_DS3231 rtc;

//pins for the line reader
int l = 9;
int lf = 8;
int rf = 7;
int r = 6;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please make sure correct part is plugged in");
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  delay(1000);
  display.clearDisplay();
  
  
  display.setCursor(0,0);
  display.println("hello world");
    
  if(! rtc.begin()){
    Serial.println("Connect RTC");
    Serial.println("Reset me please");
    while(true);
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  

}

void loop() {
  // put your main code here, to run repeatedly:
  checkLine();
  //  DateTime now = rtc.now();
  
  
  
  
}


void checkLine(){

  display.clearDisplay();
  display.setCursor(0,9);
  pinMode(l,OUTPUT);
  digitalWrite(l,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(l,INPUT);
  delayMicroseconds(SCANDELAY);
  byte readVal = digitalRead(l);
  display.print(readVal);display.print("   ");
  
  pinMode(lf,OUTPUT);
  digitalWrite(lf,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(lf,INPUT);
  delayMicroseconds(SCANDELAY);
  readVal = digitalRead(lf);
  display.print(readVal);display.print("   ");
  
  pinMode(rf,OUTPUT);
  digitalWrite(rf,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(rf,INPUT);
  delayMicroseconds(SCANDELAY);
  readVal = digitalRead(rf);
  display.print(readVal);display.print("   ");
  
  pinMode(r,OUTPUT);
  digitalWrite(r,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(r,INPUT);
  delayMicroseconds(SCANDELAY);
  readVal = digitalRead(r);
  display.print(readVal);

  DateTime now = rtc.now();
  
  display.setCursor(0,1);
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.print(" ");
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);


  //delay h
  delay(500);

}



