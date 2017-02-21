/**
 * connectWifi.cpp
 * 
  Created by SAFE24, February 18, 2017.
 */

#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include <ESP8266WiFiMulti.h>
/**
   Function that establishes a connection to the specified host
*/
void connectWifi(const char ssid[], const char password[]) {
  ESP8266WiFiMulti WiFiMulti;
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFiMulti.addAP(ssid, password);
  delay(10);

  int connectionTimeOut = 0; //Iterator to interrupt the attempt to connect to host
  //Trying to connect and waits until connected to the specified host
  while (WiFiMulti.run() != WL_CONNECTED) {
    WiFiMulti.addAP(ssid, password);
    delay(500);
    connectionTimeOut++;
    //When 10 seconds has passed the attempt to establish connection is aborted
    if (connectionTimeOut > 20) {
      Serial.println("Connection timedout... Couldn't connect to host.");
    }
  }
  Serial.println("IP adress : ");
  Serial.println(WiFi.localIP());
}

/**
   Checks the the WiFi connection
*/
int checkConnection() {
  ESP8266WiFiMulti WiFiMulti;
  int result = 0; //no connection
  if ( WiFiMulti.run() == WL_CONNECTED) {
    result = 1; //connection established
  } else {
    result = 0; //no connection

  }
  return result;
  Serial.println(result);
}

