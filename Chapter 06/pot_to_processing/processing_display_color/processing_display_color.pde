/*
Exploring Arduino - Code Listing 6-7: Processing Code to Read Data and Change Color on the Screen
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Processing Sketch to Read Value and Change Color on the Screen

//Import and initialize serial port library
import processing.serial.*;
Serial port;

float brightness = 0; //For holding value from pot

void setup()
{
  size(500,500);                         //Window size
  port = new Serial(this, "COM3", 9600); //Set up serial
  port.bufferUntil('\n');                //Set up port to read until newline
}

void draw()
{
  background(0,0,brightness); //Updates the window
}
 
void serialEvent (Serial port)
{
  brightness = float(port.readStringUntil('\n')); //Gets val
}

