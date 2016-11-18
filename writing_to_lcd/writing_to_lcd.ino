#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

#define SCANDELAY 250


//initializes communication with the lcd screen.
LiquidCrystal lcd(12,11,5,4,3,2);
RTC_DS3231 rtc;

//pins for the line reader
int l = 9;
int lf = 8;
int rf = 7;
int r = 6;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur"};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  lcdInit();
  
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

void readTime(){
  DateTime now = rtc.now();
  
  lcd.setCursor(0,1);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);

  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

void lcdInit(){
  lcd.begin(16,2);
  lcd.print("hello world");
  lcd.setCursor(0,1);
  lcd.print("Init complete");
}


void checkLine(){

  lcd.clear();
  pinMode(l,OUTPUT);
  digitalWrite(l,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(l,INPUT);
  delayMicroseconds(SCANDELAY);
  byte readVal = digitalRead(l);
  lcd.print(readVal);lcd.print("   ");
  
  pinMode(lf,OUTPUT);
  digitalWrite(lf,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(lf,INPUT);
  delayMicroseconds(SCANDELAY);
  readVal = digitalRead(lf);
  lcd.print(readVal);lcd.print("   ");
  
  pinMode(rf,OUTPUT);
  digitalWrite(rf,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(rf,INPUT);
  delayMicroseconds(SCANDELAY);
  readVal = digitalRead(rf);
  lcd.print(readVal);lcd.print("   ");
  
  pinMode(r,OUTPUT);
  digitalWrite(r,HIGH);
  delayMicroseconds(SCANDELAY);
  pinMode(r,INPUT);
  delayMicroseconds(SCANDELAY);
  readVal = digitalRead(r);
  lcd.print(readVal);

  DateTime now = rtc.now();
  
  lcd.setCursor(0,1);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(" ");
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);


  //delay h
  delay(500);

}




