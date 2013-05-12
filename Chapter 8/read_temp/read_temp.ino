/*
Exploring Arduino - Code Listing 8-1: Temperature Sensor Printing Code
http://www.exploringarduino.com/content/ch8

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Reads Temp from I2C temperature sensor
//and prints it on the serial port

//Include Wire I2C library
#include <Wire.h>
int temp_address = 72; //1001000 written as decimal number

void setup()
{
  //Start serial communication at 9600 baud
  Serial.begin(9600);
 
  //Create a Wire object
  Wire.begin();
}

void loop()
{
  //Send a request
  //Start talking to the device at the specified address
  Wire.beginTransmission(temp_address); 
  //Send a bit asking for register zero, the data register
  Wire.write(0); 
  //Complete Transmission 
  Wire.endTransmission(); 
 
  //Read the temperature from the device
  //Request 1 Byte from the specified address
  Wire.requestFrom(temp_address, 1); 
  //wait for response 
  while(Wire.available() == 0);
  // Get the temp and read it into a variable
  int c = Wire.read(); 
 
  //Do some math to convert the Celsius to Fahrenheit
  int f = round(c*9.0/5.0 +32.0);
 
  //Send the temperature in degrees C and F to the serial monitor
  Serial.print(c);
  Serial.print("C ");
  Serial.print(f);
  Serial.println("F");
 
  delay(500);
}

