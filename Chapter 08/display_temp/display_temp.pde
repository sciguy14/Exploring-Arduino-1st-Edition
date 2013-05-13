/*
Exploring Arduino - Code Listing 8-3: Processing Sketch for Displaying Temperature Values
http://www.exploringarduino.com/content/ch8

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Displays the temperature recorded by an I2C temp sensor

import processing.serial.*;
Serial port;
String temp_c = "";
String temp_f = "";
String data = "";
int index = 0;
PFont font;

void setup()
{
  size(400,400);
//Change "COM9" to the name of the serial port on your computer
  port = new Serial(this, "COM9", 9600);
  port.bufferUntil('.'); 
//Change the font name to reflect the name of the font you created
  font = loadFont("AgencyFB-Bold-200.vlw");
  textFont(font, 200);
}

void draw()
{
  background(0,0,0);
  fill(46, 209, 2);
  text(temp_c, 70, 175);
  fill(0, 102, 153);
  text(temp_f, 70, 370);
}
 
void serialEvent (Serial port)
{
  data = port.readStringUntil('.');
  data = data.substring(0, data.length() - 1);
 
  //Look for the comma between Celcius and Farenheit
  index = data.indexOf(",");
  // fetch the C Temp
  temp_c = data.substring(0, index);
  //Fetch the F temp
  temp_f = data.substring(index+1, data.length());
}

