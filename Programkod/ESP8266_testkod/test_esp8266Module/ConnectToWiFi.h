/*
  ConnectToWiFi.h - Library for connecting to WiFi-network.
  Created by SAFE24, Januari 20, 2017.
  Released into the public domain.
*/
#ifndef ConncetToWiFi_h
#define ConncetToWiFi_h


#include "Arduino.h"
#include "ESP8266WiFi.h"





class ConnectToWifi{
  public:
    void connectToWiFi(char* ssid, char* password);
    uint8_t MAC_array[6];
    char MAC_char[18];
    //const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
    const String devid = "vBDE0176C74D864E"; //device ID on Pushingbox for our Scenario
};

#endif

