/*
Exploring Arduino - Code Listing 6-8: Processing Sketch to Set Arduino RGB Colors
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

import processing.serial.*; //Import Serial Library
PImage img;                 //Image Object	
Serial port;                //Serial Port Object

void setup()
{
  size(640,256); //Size of HSV Image
  img = loadImage("hsv.jpg"); //Load in Background Image
  port = new Serial(this, "COM9", 9600); //Open Serial port
  
}

void draw()
{
  background(0);    //Black Background
  image(img,0,0);   //Overlay  image
}

void mousePressed() 
{
  color c = get(mouseX, mouseY); //Get the RGB color where mouse was pressed
  String colors = int(red(c))+","+int(green(c))+","+int(blue(c))+"\n"; //extract values from color
  print(colors); //print colors for debugging
  port.write(colors); //Send values to Arduino
}
