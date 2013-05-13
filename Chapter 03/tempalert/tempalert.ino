/*
Exploring Arduino - Code Listing 3-2: Temperature Alert Sketch
http://www.exploringarduino.com/content/ch3

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Temperature Alert!
const int BLED=9;          //Blue LED on Pin 9
const int GLED=10;         //Green LED on Pin 10
const int RLED=11;         //Red LED on Pin 11
const int TEMP=0;          //Temp Sensor is on pin A0

const int LOWER_BOUND=139; //Lower Threshold
const int UPPER_BOUND=147; //Upper Threshold

int val = 0;               //Variable to hold analog reading


void setup()
{
  pinMode (BLED, OUTPUT); //Set Blue LED as Output
  pinMode (GLED, OUTPUT); //Set Green LED as Output
  pinMode (RLED, OUTPUT); //Set Red LED as Output
}

void loop()
{
  val = analogRead(TEMP);
 
  if (val < LOWER_BOUND)
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
  else if (val > UPPER_BOUND)
  {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  else
  {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
}

