/*
Exploring Arduino - Code Listing 3-1: Potentiometer Reading Sketch
http://www.exploringarduino.com/content/ch3

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Potentiometer Reading Program

const int POT=0;  //Pot on Analog Pin 0
int val = 0;      //variable to hold the analog reading from the POT

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  val = analogRead(POT);
  Serial.println(val);
  delay(500);
}

