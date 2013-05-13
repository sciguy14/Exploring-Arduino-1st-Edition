/*
Exploring Arduino - Code Listing 14-2: Web Server Code
http://www.exploringarduino.com/content/ch13

Copyright 2013 Jeremy Blum ( http://www.jeremyblum.com )
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License v3 as published by
the Free Software Foundation.
*/

//Arduino Web Server
//Some code adapted under MIT License from
//http://bildr.org/2011/06/arduino-ethernet-pin-control/

#include <Ethernet.h>
#include <SPI.h>

const int BLUE    =5;
const int GREEN   =6;
const int RED     =7;
const int SPEAKER =3;

//For controlling LEDS and the speaker
//If you want to control additional things, add variables to control them here.
int freq = 0;
int pin;

//Set to your MAC address!
//It should be on your sticker. If you can't find it,
//make one up, or use this one.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x4A, 0xE0 };

//Start the server on port 80
EthernetServer server = EthernetServer(80); //port 80

boolean receiving = false; //To keep track of whether we are getting data.

void setup()
{
  Serial.begin(9600);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  //Connect with DHCP
  if (!Ethernet.begin(mac))
  {
    Serial.println("Could not Configure Ethernet with DHCP.");
    return;
  }
  else
  {
    Serial.println("Ethernet Configured!");
  }

  //Start the server
  server.begin();
  Serial.print("Server Started.\nLocal IP: ");
  Serial.println(Ethernet.localIP());
 
}

void loop()
{
  EthernetClient client = server.available();

  if (client)
  {

   //An HTTP request ends with a blank line
   boolean currentLineIsBlank = true;
   boolean sentHeader = false;

   while (client.connected())
   {
     if (client.available())
     {
       char c = client.read(); //Read from the incoming buffer

       if(receiving && c == ' ') receiving = false; //done receiving
       if(c == '?') receiving = true; //found arguments

       //This looks at the GET requests
       if(receiving)
       {
         //An LED command is specified with an L
         if (c == 'L')
         {
           Serial.print("Toggling Pin ");
           pin = client.parseInt();
           Serial.println(pin);
           digitalWrite(pin, !digitalRead(pin));
           break;
         }
         //A speaker command is specified with an S
         else if (c == 'S')
         {
           Serial.print("Setting Frequency to ");
           freq = client.parseInt();
           Serial.println(freq);
           if (freq == 0)
             noTone(SPEAKER);
           else
             tone(SPEAKER, freq);
           break;
         }
         //Add similarly formatted else if statements here
         //TO CONTROL ADDITIONAL THINGS
       }
    
       //Print out the response header and the HTML page
       if(!sentHeader)
       {
          //Send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html\n");
     
          //Red toggle button
          client.println("<form action='' method='get'>");
          client.println("<input type='hidden' name='L' value='7' />");
          client.println("<input type='submit' value='Toggle Red' />");
          client.println("</form>");
     
          //Green toggle button
          client.println("<form action='' method='get'>");
          client.println("<input type='hidden' name='L' value='6' />");
          client.println("<input type='submit' value='Toggle Green' />");
          client.println("</form>");
     
          //Blue toggle button
          client.println("<form action='' method='get'>");
          client.println("<input type='hidden' name='L' value='5' />");
          client.println("<input type='submit' value='Toggle Blue' />");
          client.println("</form>");
     
          //Speaker frequency slider
          client.println("<form action='' method='get'>");
          client.print("<input type='range' name='S' min='0' max='1000' step='100' value='0'/>");
          client.println("<input type='submit' value='Set Frequency' />");
          client.println("</form>");
     
          //Add additional forms forms for controlling more things here.
     
          sentHeader = true;
        }

        if (c == '\n' && currentLineIsBlank) break;

        if (c == '\n')
        {
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          currentLineIsBlank = false;
        }
      }
    }
    delay(5); //Give the web browser time to receive the data
    client.stop(); //Close the connection:
  }
}

