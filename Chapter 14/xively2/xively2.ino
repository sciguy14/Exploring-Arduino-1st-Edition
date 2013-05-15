/*
Exploring Arduino - Code Listing 14-4: Xively Datastream Upload Code Updated to Read Multiple Sensors
http://www.exploringarduino.com/content/ch13

Single Sensor Example (14-3) Created by Xively (TM) ( https://github.com/xively/xively-arduino )
Mutliple Sensor Updates by Jeremy Blum ( http://www.jeremyblum.com )
*/

#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>

// MAC address for your Ethernet shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x4A, 0xE0 };

// Your Xively key to let you upload data
char xivelyKey[] = "qkjXS1oUKqbCG-hqh3fw4WIsdvOSAKx4ZXZYSWhGUWdxcz0g";

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int lightPin = 2; //Temperature Sensor
int tempPin  = 3; //Light Sensor

// Define the strings for our datastream IDs
char lightId[] = "light_reading";
char tempId[]  = "temp_reading";
XivelyDatastream datastreams[] = {
  XivelyDatastream(lightId, strlen(lightId), DATASTREAM_FLOAT),
  XivelyDatastream(tempId, strlen(tempId), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(1242622121, datastreams, 2 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Starting double datastream upload to Xively...");
  Serial.println();

  while (Ethernet.begin(mac) != 1)
  {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }
}

void loop() {
  int lightValue = analogRead(lightPin);
  datastreams[0].setFloat(lightValue);

  Serial.print("Read light value ");
  Serial.println(datastreams[0].getFloat());
  
  int tempValue = analogRead(tempPin);
  datastreams[1].setFloat(tempValue);

  Serial.print("Read temp value ");
  Serial.println(datastreams[1].getFloat());

  Serial.println("Uploading it to Xively");
  int ret = xivelyclient.put(feed, xivelyKey);
  Serial.print("xivelyclient.put returned ");
  Serial.println(ret);

  Serial.println();
  delay(15000);
}
