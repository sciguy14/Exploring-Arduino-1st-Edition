/*
Exploring Arduino - Code Listing 6-3: Arduino Serial Echo Test
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Echo every character

char data; //holds incoming character

void setup()
{
  Serial.begin(9600); //Serial Port at 9600 baud
}

void loop()
{
  //Only print when data is received
  if (Serial.available() > 0)
  {
    data = Serial.read(); //read byte of data
    Serial.print(data);   //print byte of data
  }
}

