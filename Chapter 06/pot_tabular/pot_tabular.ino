/*
Exploring Arduino - Code Listing 6-2: Tabular Printing using Special Characters
http://www.exploringarduino.com/content/ch6

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Tabular Serial Printing Test with a Potentiometer

const int POT=0;  //Pot on Analog Pin 0

void setup()
{
  Serial.begin(9600); //Start Serial Port with Baud = 9600
}

void loop()
{
  Serial.println("\nAnalog Pin\tRaw Value\tPercentage");
  Serial.println("------------------------------------------");
  for (int i = 0; i < 10; i++)
  {
    int val = analogRead(POT);           //Read Potentiometer
    int per = map(val, 0, 1023, 0, 100); //Convert to Percentage
  
    Serial.print("A0\t\t");
    Serial.print(val);
    Serial.print("\t\t");     
    Serial.print(per);           //Print Percentage Analog Value
    Serial.println("%");         //Print % Sign and Newline
    delay(1000);                 //Wait 1 second, then repeat
  }  
}

