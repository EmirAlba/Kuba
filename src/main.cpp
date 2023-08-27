#include <Wire.h>           
#include <RTClib.h>          
#include <LiquidCrystal.h>      
#include <IRremote.h>
#include <SPI.h>

const int RS = 5;
const int E = 6;
const int D4 = 10;
const int D5 = 11;
const int D6 = 12;
const int D7 = 13;

const int irReceiverPin = 22;

bool uhrzeit = false;
bool uhrzeitModus = false;
bool hauptmenu = true;

const unsigned long button1Code = 0xF30CFF00;

int year;
int month;
int day;
int hour;
int minute;
int second;

RTC_DS3231 rtc;              
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

const int alarmHour = 8;
const int alarmMinute = 0;
bool alarmTriggered = false;

void setup() {
  Serial.begin(9600);         
  Wire.begin();           
  rtc.begin();                
  lcd.begin(16, 2);
  IrReceiver.begin(irReceiverPin, false);
}

void loop() {
DateTime now = rtc.now();

    if (IrReceiver.decode()) {
        if (hauptmenu) {
            if (IrReceiver.decodedIRData.decodedRawData == button1Code){
                hauptmenu = false;
                uhrzeitModus = true;
                uhrzeit = true;
            }
        }
    }

    if(uhrzeit){
        year = now.year();
        month = now.month();
        day = now.day();
        hour = now.hour();
        minute = now.minute();
        second = now.second();

        lcd.clear();                 
        lcd.setCursor(0, 0);        
        lcd.print("Dt: ");
        lcd.print(year);
        lcd.print("-");
        lcd.print(month);
        lcd.print("-");
        lcd.print(day);
  
        lcd.setCursor(0, 1);
        lcd.print("Uhr: ");
        lcd.print(hour);
        lcd.print(":");
        lcd.print(minute);
        lcd.print(":");
        lcd.print(second);

    if (hour == alarmHour && minute == alarmMinute && !alarmTriggered) {
        lcd.clear();
        lcd.print("Wecker klingelt!");
        alarmTriggered = true;
    }
  }
}

