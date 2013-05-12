/*
Exploring Arduino - Code Listing 4-5: Sweeping Distance Sensor
http://www.exploringarduino.com/content/ch4

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Sweeping Distance Sensor
#include <Servo.h>

 const int SERVO  =9;   //Servo on Pin 9
 const int IR     =0;   //IR Distance Sensor on Analog Pin 0
 const int LED1   =3;   //LED Output 1
 const int LED2   =5;   //LED Output 2
 const int LED3   =6;   //LED Output 3
 const int LED4   =11;  //LED Output 4

Servo myServo;     //Servo Object
int dist1 = 0;     //Quadrant 1 Distance
int dist2 = 0;     //Quadrant 2 Distance
int dist3 = 0;     //Quadrant 3 Distance
int dist4 = 0;     //Quadrant 4 Distance

void setup()
{
    myServo.attach(SERVO); //Attach the Servo
    pinMode(LED1, OUTPUT); //Set LED to Output
    pinMode(LED2, OUTPUT); //Set LED to Output
    pinMode(LED3, OUTPUT); //Set LED to Output
    pinMode(LED4, OUTPUT); //Set LED to Output
}

void loop()
{
    //Sweep the Servo into 4 regions and change the LEDs
    dist1 = readDistance(15);     //Measure IR Distance at 15 degrees
    analogWrite(LED1, dist1);     //Adjust LED Brightness
    delay(300);                   //delay before next measurement
 
    dist2 = readDistance(65);     //Measure IR Distance at 65 degrees
    analogWrite(LED2, dist2);     //Adjust LED Brightness
    delay(300);                   //delay before next measurement
 
    dist3 = readDistance(115);    //Measure IR Distance at 115 degrees
    analogWrite(LED3, dist3);     //Adjust LED Brightness
    delay(300);                   //delay before next measurement
 
    dist4 = readDistance(165);    //Measure IR Distance at 165 degrees
    analogWrite(LED4, dist4);     //Adjust LED Brightness
    delay(300);                   //delay before next measurement
}

int readDistance(int pos)
{
    myServo.write(pos);                //Move to given position
    delay(600);                        //Wait for Servo to move
    int dist = analogRead(IR);         //Read IR Sensor
    dist = map(dist, 50, 500, 0, 255); //scale it to LED range 
    dist = constrain(dist, 0, 255);    //Constrain it
    return dist;                       //Return scaled distance
}

