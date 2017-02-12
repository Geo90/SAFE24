


/*
    Main
*/
#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include "manageCamera.h"
#include "schedule.h"


const char* ssid     = "TP-LINK_7B0E";
const char* password = "23263345";
const String camera_ip = "192.168.0.70";
const String guardTourPort = "9";
const char* authorizationID = "root";
const char* authorizationPSWD = "pass";

//The esp module IP, gateway and subnet adresses
  IPAddress esp_ip (192, 168, 0, 21);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(0, 0, 0, 0);



void setup() {
  
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // Connecting to a WiFi network
 connectWifi(esp_ip, dns, gateway, subnet, ssid, password);
}

void loop() {
  setAuthorization(camera_ip, authorizationID, authorizationPSWD);
  Serial.println(sendToCamera(camera_ip, activateVirtualPort (guardTourPort)));
  delay(10000);
  setAuthorization(camera_ip, authorizationID, authorizationPSWD);
  Serial.println(sendToCamera(camera_ip, deactivateVirtualPort (guardTourPort)));
  delay(10000);
  
// Try to connect the WiFi network as long as the connection is down
  while (!checkConnection());
  connectWifi(esp_ip, dns, gateway, subnet, ssid, password);

}


