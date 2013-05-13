 /**
 * Cosm Arduino sensor client example.
 *
 * This sketch demonstrates connecting an Arduino to Cosm (https://cosm.com),
 * using the new Arduino library to send and receive data.
 *
 * Requirements
 *   * Arduino with Ethernet shield or Arduino Ethernet (board must use the
 *     Wiznet Ethernet chipset)
 *   * Arduino software with version >= 1.0
 *   * An account at Cosm (https://cosm.com)
 *
 * Sensors
 *   * Light Sensor on Analog Pin 2
 *   * Temp Sensor on Analog Pin 3
 *
 * Created 8th January, 2013 using code written by Adrian McEwen with
 * modifications by Sam Mulube
 *
 * Updated 11th April, 2013 by Jeremy Blum to support transmitting two sensor values
 * Exploring Arduino - Chapter 14, Listing 14-3.
 * http://www.exploringarduino.com/content/ch14
 *
 * Full tutorial available here: https://cosm.com/docs/quickstart/arduino.html
 *
 * This code is in the public domain.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Cosm.h>

#define API_KEY "PUT_YOUR_KEY_HERE!!!" //Your Cosm API key
#define FEED_ID PUT_YOUR_FEED_ID_HERE!!! //Your Cosm feed ID

//MAC address for your Ethernet shield
byte mac[] = { PUT_YOUR_MAC_ADDRESS_HERE };

//Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int light = 2;
int temp = 3;

unsigned long lastConnectionTime = 0;        // last time we connected to Cosm
const unsigned long connectionInterval = 15000;   // connection delay

//Initialize the Cosm library

//Define the string for our datastream ID
char lightId[] = "light_reading";
char tempId[] = "temp_reading";


CosmDatastream datastreams[] = {
  CosmDatastream(lightId, strlen(lightId), DATASTREAM_FLOAT),
  CosmDatastream(tempId,strlen(tempId), DATASTREAM_FLOAT),
};

//Wrap the datastream into a feed
CosmFeed feed(FEED_ID, datastreams, 2 /* number of datastreams */);

EthernetClient client;
CosmClient Cosmclient(client);

void setup() {
  //Put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Cosm Sensor Client Example");
  Serial.println("==========================");

  Serial.println("Initializing network");
  while (Ethernet.begin(mac) != 1) {
     Serial.println("Error getting IP address via DHCP, trying again...");
  delay(15000);
  }

  Serial.println("Network initialized");
  Serial.println();
}

void loop() {
  //Main program loop
  if (millis() - lastConnectionTime > connectionInterval) {
    //Read a value from the pin
    int lightValue = analogRead(light);
    int tempValue = analogRead(temp);
    //Send it to Cosm
    sendData(lightValue, tempValue);
    //Read the datastream back from Cosm
    getData();
    //Update connection time so we wait before connecting again
    lastConnectionTime = millis();
  }
}

//Send the supplied value to Cosm, printing some debug information as we go
void sendData(int sensorValue1, int sensorValue2) {
  datastreams[0].setFloat(sensorValue1);
  datastreams[1].setFloat(sensorValue2);

  Serial.print("Read light value ");
  Serial.println(datastreams[0].getFloat());
 
  Serial.print("Read temp value ");
  Serial.println(datastreams[1].getFloat());

  Serial.println("Uploading to Cosm");
  int ret = Cosmclient.put(feed, API_KEY);
  Serial.print("PUT return code: ");
  Serial.println(ret);

  Serial.println();
}

//Get the value of the datastream from Cosm, printing out the value we received
void getData() {
  Serial.println("Reading data from Cosm");

  int ret = Cosmclient.get(feed, API_KEY);
  Serial.print("GET return code: ");
  Serial.println(ret);

  if (ret > 0) {
    Serial.print("Datastream is: ");
    Serial.println(feed[0]);
    Serial.println(feed[1]);

    Serial.print("Light value is: ");
    Serial.println(feed[0].getFloat());
  
    Serial.print("Temp value is: ");
    Serial.println(feed[1].getFloat());
  }

  Serial.println();
}

