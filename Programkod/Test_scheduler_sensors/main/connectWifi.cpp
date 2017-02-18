
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
  while (WiFiMulti.run() != WL_CONNECTED || connectionTimeOut > 10) {
    delay(500);
    connectionTimeOut++;
    //When 10 seconds has passed the attempt to establish connection is aborted
    if (connectionTimeOut > 10) {
      Serial.println("Connections timedout... Couldn't connect to host.");
    }
  }
  Serial.println("IP adress : ");
  Serial.println(WiFi.localIP());
}


//Funktion checks the WiFi connection
int checkConnection() {
  ESP8266WiFiMulti WiFiMulti;
  int result;
  if ( WiFiMulti.run() == WL_CONNECTED) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

