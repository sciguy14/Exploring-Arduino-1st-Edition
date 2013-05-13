/*
Exploring Arduino - Code Listing 2-2: LED with Changing Blink Rate
http://www.exploringarduino.com/content/ch2

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

const int LED=9;         //define LED for Pin 9
void setup()
{
  pinMode (LED, OUTPUT); //Set the LED pin as an output
}

void loop()
{
  for (int i=100; i<=1000; i=i+100)
  {
    digitalWrite(LED, HIGH);
    delay(i);
    digitalWrite(LED, LOW);
    delay(i);
  }
}

