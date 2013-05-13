/*
Exploring Arduino - Code Listing 10-1: LCD Text with an Incrementing Number
http://www.exploringarduino.com/content/ch10

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//LCD text with incrementing number

//Include the library code:
#include <LiquidCrystal.h>

//Start the time at 0
int time = 0;

//Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
  //Set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Jeremy's Display");
}

void loop()
{
  //Move cursor to second line, first position
  lcd.setCursor(0,1);
  //Print Current Time
  lcd.print(time);  
  //Wait 1 second
  delay(1000);
  //Increment the time
  time++; 
}

