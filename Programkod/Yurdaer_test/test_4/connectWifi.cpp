

#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include <ESP8266WiFiMulti.h>

/**
 * Function that establishes a connection to the specified host
 */
void connectWifi(IPAddress esp_ip, IPAddress gateway, IPAddress subnet, const char ssid[], const char password[]) {
  ESP8266WiFiMulti WiFiMulti;
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //Checks if password needed of not and connects to the host
  if (sizeof(password) != 1) {
    
    WiFiMulti.addAP(ssid,password);
  //  WiFi.begin(ssid, password);
    WiFi.config(esp_ip, gateway, subnet);
  }
  else {
    WiFi.begin(ssid);
    WiFi.config(esp_ip, gateway, subnet);
  }

  
  int connectionTimeOut = 0; //Iterator to interrupt the attempt to connect to host
  //Trying to connect and waits until connected to the specified host
  while (WiFiMulti.run() != WL_CONNECTED || connectionTimeOut>20) {
    delay(500);
    connectionTimeOut++;
    //When 10 seconds has passed the attempt to establish connection is aborted
    if(connectionTimeOut>20){
     Serial.println("Connections timedout... Couldn't connect to host.");
    }
  }
}

