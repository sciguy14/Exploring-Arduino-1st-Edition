/*
Exploring Arduino - Code Listing 13-1: SD Card Write Test
http://www.exploringarduino.com/content/ch13

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Write to SD card

#include <SD.h>

//Set by default for the SD card library
//MOSI = Pin 11
//MISO = Pin 12
//SCLK = PIN 13
//We always need to set the CS Pin
const int CS_PIN  =10;

//We set this high to provide power
const int POW_PIN =8;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing Card");
  //CS pin is an output
  pinMode(CS_PIN, OUTPUT);
 
  //Card will draw power from pin 8, so set it high
  pinMode(POW_PIN, OUTPUT); 
  digitalWrite(POW_PIN, HIGH);
 
  if (!SD.begin(CS_PIN))
  {
    Serial.println("Card Failure");
    return;
  }
  Serial.println("Card Ready"); 
}

void loop()
{
  long timeStamp = millis();
  String dataString = "Hello There!";
 
  //Open a file and write to it. 
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.println(dataString);
    dataFile.close(); //Data isn't actually written until we close the connection!
  
    //Print same thing to the screen for debugging
    Serial.print(timeStamp);
    Serial.print(",");
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  delay(5000);
}

