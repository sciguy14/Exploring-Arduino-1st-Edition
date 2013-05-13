/*
Exploring Arduino - Code Listing 6-10: Light-Based Computer Lock
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Locks your computer when you turn off the lights

const int LIGHT     =1;    //Light sensor on analog pin 1
const int THRESHOLD =500;  //Brightness must drop below this level to lock computer

void setup()
{
  Keyboard.begin(); 
}

void loop()
{
  int brightness = analogRead(LIGHT);    //Read the light level
 
  if (brightness < THRESHOLD)
  {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('l');
    delay(100);
    Keyboard.releaseAll();
  }
}

