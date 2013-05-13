/*
Exploring Arduino - Code Listing 2-3: LED Fade Sketch
http://www.exploringarduino.com/content/ch2

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

const int LED=9;   //define LED for Pin 9
void setup()
{
  pinMode (LED, OUTPUT);    //Set the LED pin as an output
}

void loop()
{
  for (int i=0; i<256; i++)
  {
    analogWrite(LED, i);
    delay(10);
  }
  for (int i=255; i>=0; i--)
  {
    analogWrite(LED, i);
    delay(10);
  }
}

