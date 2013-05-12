/*
Exploring Arduino - Code Listing 4-4: Servo Potentiometer Control
http://www.exploringarduino.com/content/ch4

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Servo Potentiometer Control

#include <Servo.h>

const int SERVO=9; //Servo on Pin 9
const int POT=0;    //POT on Analog Pin 0

Servo myServo;
int val = 0;     //for storing the reading from the POT

void setup()
{
    myServo.attach(SERVO);
}

void loop()
{
    val = analogRead(POT);           //Read Pot
    val = map(val, 0, 1023, 0, 179); //scale it to servo range 
    myServo.write(val);              // sets the servo 
    delay(15);                       // waits for the servo
}

