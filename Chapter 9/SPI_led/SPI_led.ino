/*
Exploring Arduino - Code Listing 9-1: SPI Control of Multiple Digital Potentiometers
http://www.exploringarduino.com/content/ch9

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Changes LED brightness using voltage input instead of PWM

//Include SPI library
#include <SPI.h>

//When using the SPI library, you only have to worry
//about picking your slave selects
//By default, 11 = MOSI, 12 = MISO, 13 = CLK
const int SS1=10; //Slave Select Chip 1
const int SS2=9;  //Slave Select Chip 2

const byte REG0=B00000000; //Register 0 Write command
const byte REG1=B00010000; //Register 1 Write command

void setup()
{
  //Set pin directions for SS
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
 
  //Initialize SPI
  SPI.begin();
}

//This will set 1 LED to the specififed level
//Chip 1 (SS 10) Register 0 is Red
//Chip 1 (SS 10) Resiter 1 is Yellow
//Chip 2 (SS 9) Register 0 is Green
//Chip 2 (SS 9) Register 1 is Blue
void setLed(int SS, int reg, int level)
{
  digitalWrite(SS, LOW); //Set the given SS pin low
  SPI.transfer(reg);   //Choose the register to write to
  SPI.transfer(level);  //Set the LED level (0-128)
  digitalWrite(SS, HIGH); //Set the given SS pin high again
}

void loop()
{
  for (int i=0; i<=128; i++)
  {
    setLed(SS1, REG0, i);
    setLed(SS1, REG1, i);
    setLed(SS2, REG0, i);
    setLed(SS2, REG1, i);
    delay(10);
  }
  delay(300);
  for (int i=128; i>=0; i--)
  {
    setLed(SS1, REG0, i);
    setLed(SS1, REG1, i);
    setLed(SS2, REG0, i);
    setLed(SS2, REG1, i);
    delay(10);
  } 
  delay(300);
}

