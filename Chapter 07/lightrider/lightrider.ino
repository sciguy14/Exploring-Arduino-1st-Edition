/*
Exploring Arduino - Code Listing 7-2: Light Rider Sequence Code
http://www.exploringarduino.com/content/ch7

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Make a light rider animation

const int SER   =8;    //Serial Output to Shift Register
const int LATCH =9;    //Shift Register Latch Pin
const int CLK   =10;   //Shift Register Clock Pin

//Sequence of LEDs
int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2};

void setup()
{
  //Set pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop()
{
  for (int i = 0; i < 14; i++)
  {
    digitalWrite(LATCH, LOW);             //Latch Low - start sending data
    shiftOut(SER, CLK, MSBFIRST, seq[i]); //Send data, Most Significant Bit first
    digitalWrite(LATCH, HIGH);            //Latch High - stop sending data
    delay(100);                           //Animation Speed
  }
}

