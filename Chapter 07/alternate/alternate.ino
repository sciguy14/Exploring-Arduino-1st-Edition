/*
Exploring Arduino - Code Listing 7-1: Alternating LED Pattern on a Shift Register
http://www.exploringarduino.com/content/ch7

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

const int SER   =8;    //Serial Output to Shift Register
const int LATCH =9;    //Shift Register Latch Pin
const int CLK   =10;   //Shift Register Clock Pin

void setup()
{
  //Set pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  
  digitalWrite(LATCH, LOW);                //Latch Low
  shiftOut(SER, CLK, MSBFIRST, B10101010); //Send data, Most Significant Bit first
  digitalWrite(LATCH, HIGH);               //Latch High - Display setting
}

void loop()
{
  //Do nothing
}

