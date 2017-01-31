/*
  ConnectToWiFi.cpp - Library for connecting to WiFi-network.
  Created by SAFE24, Januari 20, 2017.
  Released into the public domain.
*/


#include "ESP8266WiFi.h"
#include "ConnectToWiFi.h";

uint8_t MAC_array[6];
char MAC_char[18];

const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "vBDE0176C74D864E"; //device ID on Pushingbox for our Scenario

void connectToWifi(const char* ssid, const char* password){
    Serial.begin(115200);
    
    WiFi.macAddress(MAC_array);
    
    for (int i = 0; i < sizeof(MAC_array); ++i){
      sprintf(MAC_char,"%s%02x:",MAC_char,MAC_array[i]);
    }
    Serial.println(MAC_char);

  
    Serial.print("Connecting to: "+*ssid);
    Serial.println("going into wl connect");
    // Connect to WiFi
    WiFi.begin(ssid,password);

    // while wifi not connected yet, print '.'
    // then after it connected, get out of the loop
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
}


