/*
Exploring Arduino - Code Listing 10-3: Personal Thermostat Program
http://www.exploringarduino.com/content/ch10

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Keep yourself cool! This is a thermostat.
//This assumes temperatures are always two digits

//Include Wire I2C library and set the address
#include <Wire.h>
#define TEMP_ADDR 72

//Include the LCD library and initialize:
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Custom degree character
byte degree[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

//Custom "Fan On" indicator
byte fan_on[8] = {
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
  B00000,
};

//Custom "Fan Off" indicator
byte fan_off[8] = {
  B00100,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00000,
};

//Pin Connections
const int SPEAKER     =8;
const int DOWN_BUTTON =9;
const int UP_BUTTON   =10;
const int FAN         =11;

//Variables for debouncing
boolean lastDownTempButton = LOW;
boolean currentDownTempButton = LOW;
boolean lastUpTempButton = LOW;
boolean currentUpTempButton = LOW;

int set_temp = 23;    //The Default desired temperature
boolean one_time = false; //Used for making the speaker beep only one time

void setup()
{
  pinMode(FAN, OUTPUT);
 
  //Create a wire object for the temp sensor
  Wire.begin();
 
  //Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
 
  //Make custom characters
  lcd.createChar(0, degree);
  lcd.createChar(1, fan_off);
  lcd.createChar(2, fan_on);
 
  //Print a static message to the LCD
  lcd.setCursor(0,0);
  lcd.print("Current:");
  lcd.setCursor(10,0);
  lcd.write((byte)0);
  lcd.setCursor(11,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.setCursor(10,1);
  lcd.write((byte)0);
  lcd.setCursor(11,1);
  lcd.print("C");
  lcd.setCursor(15,1);
  lcd.write(1); 
}

//A debouncing function that can be used by multiple buttons
boolean debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(pin);
  }
  return current;
}

void loop()
{
  //Get the Temperature
  Wire.beginTransmission(TEMP_ADDR); //Start talking
  Wire.write(0);                     //Ask for register zero
  Wire.endTransmission();            //Complete transmission
  Wire.requestFrom(TEMP_ADDR, 1);    //Request 1 byte
  while(Wire.available() == 0);      //Wait for response
  int c = Wire.read();               //Get the temp in C
  lcd.setCursor(8,0);                //Move the cursor
  lcd.print(c);                      //Print this new value
  
  //Debounce both buttons
  currentDownTempButton = debounce(lastDownTempButton, DOWN_BUTTON);
  currentUpTempButton  = debounce(lastUpTempButton, UP_BUTTON);
 
  //Turn down the set temp
  if (lastDownTempButton== LOW && currentDownTempButton == HIGH)
  {
    set_temp--;
  }
  //Turn up the set temp
  else if (lastUpTempButton== LOW && currentUpTempButton  == HIGH)
  {
    set_temp++;
  }
  //Print the set temp
  lcd.setCursor(8,1);
  lcd.print(set_temp);
  lastDownTempButton = currentDownTempButton;
  lastUpTempButton = currentUpTempButton;
 
  //It's too hot!
  if (c >= set_temp)
  {
    //So that the speaker will only beep one time...  
    if (!one_time)
    { 
      tone(SPEAKER, 400);
      delay(500);
      one_time = true;
    }
    //Turn off the speaker if it's done
    else
    {
      noTone(SPEAKER);
    }
    //Turn the fan on and update display
    digitalWrite(FAN, HIGH);
    lcd.setCursor(15,1);
    lcd.write(2);
  }
  //It't not to hot!
  else
  {
    //Make sure the speaker is off, reset the “one beep” variable
    //Update the fan state, and LCD display
    noTone(SPEAKER);
    one_time = false;
    digitalWrite(FAN, LOW);
    lcd.setCursor(15,1);
    lcd.write(1);
  }
} 

