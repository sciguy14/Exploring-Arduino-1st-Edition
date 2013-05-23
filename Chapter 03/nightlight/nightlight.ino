/*
Exploring Arduino - Code Listing 3-3: Automatic Night Light Sketch
http://www.exploringarduino.com/content/ch3

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Automatic Night Light

const int RLED=9;        //Red LED on pin 9 (PWM)
const int LIGHT=0;       //Lght Sensor on Analog Pin 0
const int MIN_LIGHT=200; //Minimum expected light value
const int MAX_LIGHT=900; //Maximum Expected Light value
int val = 0;             //variable to hold the analog reading

void setup()
{
  pinMode(RLED, OUTPUT); //Set LED pin as output
}

void loop()
{
  val = analogRead(LIGHT);                      //read the light sensor
  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0); //map the light reading
  val = constrain(val, 0, 255);                 //constrain light value
  analogWrite(RLED, val);                       //control the LED
}

