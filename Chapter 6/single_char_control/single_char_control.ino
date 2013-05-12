/*
Exploring Arduino - Code Listing 6-4: Single LED Control using Characters
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Single Character Control of an LED

const int LED=9;

char data; //holds incoming character

void setup()
{
  Serial.begin(9600); //Serial Port at 9600 baud
  pinMode(LED, OUTPUT);
}

void loop()
{
  //Only act when data is available in the buffer
  if (Serial.available() > 0)
  {
    data = Serial.read(); //read byte of data
    //Turn LED on
    if (data == '1')
    {
      digitalWrite(LED, HIGH);
      Serial.println("LED ON");
    }
    //Turn LED off
    else if (data == '0')
    {
      digitalWrite(LED, LOW);
      Serial.println("LED OFF");
    }
  }

}

