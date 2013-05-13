/*
Exploring Arduino - Code Listing 13-3: SD Reading and Writing with an RTC
http://www.exploringarduino.com/content/ch13

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//SD read and write with RTC

#include <SD.h>   //For talking to SD Card
#include <Wire.h>  //For RTC
#include "RTClib.h" //For RTC

//Define pins
//SD card is on standard SPI pins
//RTC is on Standard I2C Pins
const int CS_PIN      =10;
const int SD_POW_PIN  =8;
const int RTC_POW_PIN =A3;
const int RTC_GND_PIN =A2;

//Default rate of 5 seconds
int refresh_rate = 5000;

//Define an RTC object
RTC_DS1307 RTC;

//Initialize strings
String year, month, day, hour, minute, second, time, date;

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
 
  //Read the configuration information (speed.txt)
  File commandFile = SD.open("speed.txt");
  if (commandFile)
  {
    Serial.println(F("Reading Command File"));
  
    while(commandFile.available())
    {
      refresh_rate = commandFile.parseInt();
    }
    Serial.print(F("Refresh Rate = "));
    Serial.print(refresh_rate);
    Serial.println(F("ms"));
    commandFile.close();
  }
  else
  {
    Serial.println(F("Could not read command file."));
    return;
  }
 
  //Write column headers
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(F("\nNew Log Started!"));
    dataFile.println(F("Date,Time,Phrase"));
    dataFile.close(); //Data isn't actually written until we close the connection!
  
    //Print same thing to the screen for debugging
    Serial.println(F("\nNew Log Started!"));
    Serial.println(F("Date,Time,Phrase"));
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
 
  String dataString = "Hello There!";
 
  //Open a file and write to it.
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(date);
    dataFile.print(F(","));
    dataFile.print(time);
    dataFile.print(F(","));
    dataFile.println(dataString);
    dataFile.close(); //Data isn't actually written until we close the connection!
  
    //Print same thing to the screen for debugging
    Serial.print(date);
    Serial.print(F(","));
    Serial.print(time);
    Serial.print(F(","));
    Serial.println(dataString);
  }
  else
  {
    Serial.println(F("Couldn't open log file"));
  }
  delay(refresh_rate);
}

