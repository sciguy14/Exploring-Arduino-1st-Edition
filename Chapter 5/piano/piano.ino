/*
Exploring Arduino - Code Listing 5-2: Pentatonic Micro Piano
http://www.exploringarduino.com/content/ch5

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Pentatonic Piano
//C D E G A
 
#define NOTE_C  262 //Hz
#define NOTE_D  294 //Hz
#define NOTE_E  330 //Hz
#define NOTE_G  392 //Hz
#define NOTE_A  440 //Hz

const int SPEAKER=9;   //Speaker on Pin 9

const int BUTTON_C=7;  //Button Pin
const int BUTTON_D=6;  //Button Pin
const int BUTTON_E=5;  //Button Pin
const int BUTTON_G=4;  //Button Pin
const int BUTTON_A=3;  //Button Pin


void setup()
{
 //No setup needed
 //Tone function sets outputs
}

void loop()
{
 while (digitalRead(BUTTON_C))
  tone(SPEAKER, NOTE_C);
 while(digitalRead(BUTTON_D))
  tone(SPEAKER, NOTE_D);
 while(digitalRead(BUTTON_E))
  tone(SPEAKER, NOTE_E);
 while(digitalRead(BUTTON_G))
  tone(SPEAKER, NOTE_G);
 while(digitalRead(BUTTON_A))
  tone(SPEAKER, NOTE_A);
 
 //Stop playing if all buttons have been released
 noTone(SPEAKER);
}

