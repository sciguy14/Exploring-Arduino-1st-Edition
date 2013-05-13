/*
Exploring Arduino - Code Listing 13-4: Entrance Logger Software
http://www.exploringarduino.com/content/ch13

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Logs Room Entrance Activity

#include <SD.h>   //For talking to SD Card
#include <Wire.h>  //For RTC
#include "RTClib.h" //For RTC

//Define pins
//SD Card is on Standard SPI Pins
//RTC is on Standard I2C Pins
const int CS_PIN      =10; //SS for SD Shield
const int SD_POW_PIN  =8;  //Power for SD Shield
const int RTC_POW_PIN =A3; //Used as digital output
const int RTC_GND_PIN =A2; //Used as digital output
const int IR_PIN      =0; //Analog Input 0

//Define an RTC object
RTC_DS1307 RTC;

//Initialize strings
String year, month, day, hour, minute, second, time, date;

//Initialize distance variables
int raw = 0;
int raw_prev = 0;
boolean active = false;
int update_time = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Initializing Card"));
 
  //CS pin, and pwr/gnd pins are outputs
  pinMode(CS_PIN,   OUTPUT);
  pinMode(SD_POW_PIN, OUTPUT);
  pinMode(RTC_POW_PIN, OUTPUT);
  pinMode(RTC_GND_PIN, OUTPUT);
  
  //Setup power and ground pins for both modules 
  digitalWrite(SD_POW_PIN, HIGH);
  digitalWrite(RTC_POW_PIN, HIGH);
  digitalWrite(RTC_GND_PIN, LOW);
 
  //Initiate the I2C bus and the RTC library
  Wire.begin();
  RTC.begin();
  
  //If RTC is not running, set it to the computer's compile time
  if (! RTC.isrunning())
  {
    Serial.println(F("RTC is NOT running!"));
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
 
  //Initialize SD card
  if (!SD.begin(CS_PIN))
  {
    Serial.println(F("Card Failure"));
    return;
  }
  Serial.println(F("Card Ready"));
 
  //Write Column Headers
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(F("\nNew Log Started!"));
    dataFile.println(F("Date,Time,Raw,Active"));
    dataFile.close(); //Data isn't actually written until we close the connection!
  
    //Print same thing to the screen for debugging
    Serial.println(F("\nNew Log Started!"));
    Serial.println(F("Date,Time,Raw,Active"));
  }
  else
  {
    Serial.println(F("Couldn't open log file"));
  }
 
}

void loop()
{
  //Get the current date and time info and store in strings
  DateTime datetime = RTC.now();
  year  = String(datetime.year(),  DEC);
  month = String(datetime.month(), DEC);
  day  = String(datetime.day(),  DEC);
  hour  = String(datetime.hour(),  DEC);
  minute = String(datetime.minute(), DEC);
  second = String(datetime.second(), DEC);
 
  //Concatenate the strings into date and time
  date = year + "/" + month + "/" + day;
  time = hour + ":" + minute + ":" + second;
 
  //Gather Motion Data
  raw = analogRead(IR_PIN);
  //If the value changes by more than 75 between readings, indicate movement.
  if (abs(raw-raw_prev) > 75)
    active = true;
  else
    active = false;
  raw_prev = raw;
 
  //Open a file and write to it.
  if (active || update_time == 20)
  {
    File dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile)
    {
      dataFile.print(date);
      dataFile.print(F(","));
      dataFile.print(time);
      dataFile.print(F(","));
      dataFile.print(raw);
      dataFile.print(F(","));
      dataFile.println(active);
      dataFile.close(); //Data isn't actually written until we close the connection!
   
      //Print same thing to the screen for debugging
      Serial.print(date);
      Serial.print(F(","));
      Serial.print(time);
      Serial.print(F(","));
      Serial.print(raw);
      Serial.print(F(","));
      Serial.println(active);
    }
    else
    {
      Serial.println(F("Couldn't open log file"));
    }
    update_time = 0;
  }
  delay(50);
  update_time++;
}
