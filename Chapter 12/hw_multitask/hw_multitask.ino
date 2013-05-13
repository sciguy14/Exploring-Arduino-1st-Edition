/*
Exploring Arduino - Code Listing 12-1: Hardware Interrupts for Multitasking
http://www.exploringarduino.com/content/ch12

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Use Hardware-Debounced Switch to Control Interrupt

//Button pins
const int BUTTON_INT =0;  //Interrupt 0 (pin 2 on the Uno)
const int RED        =11; //Red LED on pin 11
const int GREEN      =10; //Green LED on pin 10
const int BLUE       =9;  //Blue LED on pin 9

//Volatile variables can change inside interrupts
volatile int selectedLED = RED;

void setup()
{
  pinMode (RED, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(BUTTON_INT, swap, RISING);
}

void swap()
{
  //Turn off the current LED
  analogWrite(selectedLED, 0);
  //Then, choose a new one.
  if (selectedLED == GREEN)
    selectedLED = RED;
  else if (selectedLED == RED)
    selectedLED = BLUE;
  else if (selectedLED == BLUE)
    selectedLED = GREEN;
}

void loop()
{
  for (int i = 0; i<256; i++)
  {
    analogWrite(selectedLED, i);
    delay(10);
  }
  for (int i = 255; i>= 0; i--)
  {
    analogWrite(selectedLED, i);
    delay(10);
  }
}
