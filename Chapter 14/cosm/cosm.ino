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
 * Optional
 *   * An analog sensor connected to pin 2 (note we can still read a value from
 *     the pin without this)
 *
 * Created 8th January, 2013 using code written by Adrian McEwen with
 * modifications by Sam Mulube
 *
 * Full tutorial available here: https://cosm.com/docs/quickstart/arduino.html
 *
 * This code is in the public domain.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Cosm.h>

#define API_KEY "PUT_YOUR_KEY_HERE!!!" // your Cosm API key
#define FEED_ID PUT_YOUR_FEED_ID_HERE!!! // your Cosm feed ID

// MAC address for your Ethernet shield
byte mac[] = { PUT_YOUR_MAC_ADDRESS_HERE  };

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int sensorPin = 2;

unsigned long lastConnectionTime = 0;                // last time we connected to Cosm
const unsigned long connectionInterval = 15000;      // delay between connecting to Cosm in milliseconds

// Initialize the Cosm library

// Define the string for our datastream ID
char sensorId[] = "sensor_reading";

CosmDatastream datastreams[] = {
  CosmDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
};

// Wrap the datastream into a feed
CosmFeed feed(FEED_ID, datastreams, 1 /* number of datastreams */);

EthernetClient client;
CosmClient cosmclient(client);

void setup() {
  // put your setup code here, to run once:
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
  // main program loop
  if (millis() - lastConnectionTime > connectionInterval) {
    // read a value from the pin
    int sensorValue = analogRead(sensorPin);
    // send it to Cosm
    sendData(sensorValue);
    // read the datastream back from Cosm
    getData();
    // update connection time so we wait before connecting again
    lastConnectionTime = millis();
  }
}

// send the supplied value to Cosm, printing some debug information as we go
void sendData(int sensorValue) {
  datastreams[0].setFloat(sensorValue);

  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());

  Serial.println("Uploading to Cosm");
  int ret = cosmclient.put(feed, API_KEY);
  Serial.print("PUT return code: ");
  Serial.println(ret);

  Serial.println();
}

// get the value of the datastream from Cosm, printing out the value we received
void getData() {
  Serial.println("Reading data from Cosm");

  int ret = cosmclient.get(feed, API_KEY);
  Serial.print("GET return code: ");
  Serial.println(ret);

  if (ret > 0) {
    Serial.print("Datastream is: ");
    Serial.println(feed[0]);

    Serial.print("Sensor value is: ");
    Serial.println(feed[0].getFloat());
  }

  Serial.println();
}

    
