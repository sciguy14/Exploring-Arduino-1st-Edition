/*
Exploring Arduino - Code Listing 6-1: Potentiometer Serial Print Test Program
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Simple Serial Printing Test with a Potentiometer

const int POT=0;  //Pot on analog pin 0

void setup()
{
  Serial.begin(9600); //Start serial port with baud = 9600
}

void loop()
{
  int val = analogRead(POT);           //Read potentiometer
  int per = map(val, 0, 1023, 0, 100); //Convert to percentage
  Serial.print("Analog Reading: ");   
  Serial.print(val);                   //Print raw analog value
  Serial.print("  Percentage: ");     
  Serial.print(per);                   //Print percentage analog value
  Serial.println("%");                 //Print % sign and newline
  delay(1000);                         //Wait 1 second, then repeat
}

