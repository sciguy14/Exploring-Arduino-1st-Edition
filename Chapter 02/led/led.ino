/*
Exploring Arduino - Code Listing 2-1: Turning on an LED
http://www.exploringarduino.com/content/ch2

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

const int LED=9;               //define LED for pin 9
void setup()
{
  pinMode (LED, OUTPUT);    //Set the LED pin as an output
  digitalWrite(LED, HIGH);  //Set the LED pin high
}

void loop()
{
  //we are not doing anything in the loop!
}
