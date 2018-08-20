/*
Exploring Arduino - Code Listing 12-3: Sound Machine Code
http://www.exploringarduino.com/content/ch12

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Use Hardware and Timer Interrupts for Fun with Sound

//Include the TimerOne library
#include <TimerOne.h>

//Button pins
const int BUTTON_INT =0;  //Interrupt 0 (pin 2 on the Uno)
const int SPEAKER    =12; //Speaker on pin 12

//Music keys
#define NOTE_C 65
#define NOTE_D 73
#define NOTE_E 82
#define NOTE_F 87
#define NOTE_G 98
#define NOTE_A 110
#define NOTE_B 123

//Volatile variables can change inside interrupts
volatile int key = NOTE_C;
volatile int octave_multiplier = 1;

void setup()
{
  //Set up serial
  Serial.begin(9600);
 
  pinMode (SPEAKER, OUTPUT);
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(BUTTON_INT, changeKey, RISING);
 
  //Set up timer interrupt
  Timer1.initialize(500000); // (.5 seconds)
  Timer1.attachInterrupt(changePitch); //Runs "changePitch" on each timer interrupt
}

void changeKey()
{
  octave_multiplier = 1;
  if (key == NOTE_C)
    key = NOTE_D;
  else if (key == NOTE_D)
    key = NOTE_E;
  else if (key == NOTE_E)
    key = NOTE_F;
  else if (key == NOTE_F)
    key = NOTE_G;
  else if (key == NOTE_G)
    key = NOTE_A;
  else if (key == NOTE_A)
    key = NOTE_B;
  else if (key == NOTE_B)
    key = NOTE_C;
}

//Timer interrupt function
void changePitch()
{
  octave_multiplier = octave_multiplier * 2;
  if (octave_multiplier > 16) octave_multiplier = 1;
  tone(SPEAKER,key*octave_multiplier);
}

void loop()
{
  Serial.print("Key: ");
  Serial.print(key);
  Serial.print(" Multiplier: ");
  Serial.print(octave_multiplier);
  Serial.print(" Frequency: ");
  Serial.println(key*octave_multiplier);
  delay(100);
}

