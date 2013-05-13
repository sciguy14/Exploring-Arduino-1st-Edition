/*
Exploring Arduino - Code Listing 11-6: Receiving Arduino
http://www.exploringarduino.com/content/ch11

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Code running on an Arduino to receive doorbell value

const int RED     =11; //Red LED on pin 11
const int GREEN   =10; //Green LED on pin 10
const int SPEAKER =8;  //Speaker on pin 8

char data;                   //Char to hold incoming serial data 
int onLED = GREEN;           //Initially on LED
int offLED = RED;            //Initially off LED
int freq = 131;              //Initial speaker frequency
unsigned long prev_time = 0; //Timer for toggling the LED and speaker

void setup()
{
  Serial.begin(9600); //Start serial
}

void loop()
{
 
  //Handle light and sound toggling
  //If 100ms have passed
  if (millis() >= prev_time + 100)
  {
    //Toggle the LED state
    if (onLED == GREEN)
    {
      onLED = RED;
      offLED = GREEN;
    }
    else
    {
      onLED = GREEN;
      offLED = RED;
    }
    //Toggle the frequency
    if (freq == 261){
       freq = 131;
    } else  {
       freq = 261;
    }
    //Set the current time in ms to the 
    //Previous time for the next trip through the loop
    prev_time = millis();  
  }
 
  //Check if serial data is available
  if (Serial.available() > 0)
  { 
    //Read byte of data
    data = Serial.read(); 
    
    //If the button is pressed, play tone and turn LED on
    if (data == '1')
    {
      digitalWrite(onLED, HIGH);
      digitalWrite(offLED, LOW);
      tone(SPEAKER, freq);
    }
    //If the button is not pressed, turn the sound and light off
    else if (data == '0')
    {
      digitalWrite(onLED, LOW);
      digitalWrite(offLED, LOW);
      noTone(SPEAKER);
    }
  }
}
