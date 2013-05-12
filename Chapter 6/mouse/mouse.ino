/*
Exploring Arduino - Code Listing 6-11: Mouse Control Code for the Leonardo
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

// Make a Mouse!

const int LEFT_BUTTON   =4;  //Input pin for the left button
const int MIDDLE_BUTTON =3;  //Input pin for the middle button
const int RIGHT_BUTTON  =2;  //Input pin for the right button
const int X_AXIS        =0;  //Joystick x-axis analog pin
const int Y_AXIS        =1;  //Joystick y-axis analog pin

void setup()
{
  Mouse.begin();
}

void loop()
{
  int xVal = readJoystick(X_AXIS);         //Get x-axis movement
  int yVal = readJoystick(Y_AXIS);         //Get y-axis movement

  Mouse.move(xVal, yVal, 0);               //Move the mouse

  readButton(LEFT_BUTTON, MOUSE_LEFT);     //Control left button
  readButton(MIDDLE_BUTTON, MOUSE_MIDDLE); //Control middle button
  readButton(RIGHT_BUTTON, MOUSE_RIGHT);   //Control right button

  delay(5);                                //This controls responsiveness
}

//Reads joystick value, scales it, and adds dead range in middle
int readJoystick(int axis)
{ 
  int val = analogRead(axis);        //Read analog value
  val = map(val, 0, 1023, -10, 10);  //Map the reading

  if (val <= 2 && val >= -2)         //Create dead zone to stop mouse drift
    return 0; 
 
  else                               //Return scaled value
    return val;
}

//Read a button and issue a mouse command
void readButton(int pin, char mouseCommand)
{
  //If button is depressed, click if it hasn't already been clicked
  if (digitalRead(pin) == HIGH)
  {
    if (!Mouse.isPressed(mouseCommand))
    {
      Mouse.press(mouseCommand); 
    }
  } 
  //Release the mouse if it has been clicked.
  else
  {
    if (Mouse.isPressed(mouseCommand))
    {
      Mouse.release(mouseCommand); 
    }
  }
}

