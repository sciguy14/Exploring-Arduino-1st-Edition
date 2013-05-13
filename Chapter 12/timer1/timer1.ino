/*
Exploring Arduino - Code Listing 12-2: Simple Timer Interrupt Blink Test
http://www.exploringarduino.com/content/ch12

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Using Timer Interrupts with the Arduino
#include <TimerOne.h>
const int LED=13;
 
void setup() 
{
  pinMode(LED, OUTPUT);  
  Timer1.initialize(1000000); // set a timer of length 1000000 microseconds (1 second)
  Timer1.attachInterrupt(blinky); //Runs "blinky" on each timmer interrupt
}
 
void loop()
{
  //Put any other code here.
}
 
//Timer interrupt function
void blinky()
{
  digitalWrite(LED, !digitalRead(LED)); //Toggle LED State
}

