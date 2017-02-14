


/*
    Main
*/
#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include "manageCamera.h"
#include "schedule.h"


const char* ssid     = "TP-LINK_7B0E";
const char* passwordWifi = "23263345";
const String camera_ip = "192.168.0.70";

const String guardTourPort = "9";
const String recordPort = "1";
const char* username = "root";
const char* password = "pass";

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
  connectWifi(esp_ip, dns, gateway, subnet, ssid, passwordWifi);
}

void loop() {

  sendToCamera(camera_ip, activateVirtualPort (recordPort), username, password);
  delay(100);
  Serial.println(sendToCamera(camera_ip, activateVirtualPort (guardTourPort), username, password));

  delay(20000);

  Serial.println(sendToCamera(camera_ip, deactivateVirtualPort (guardTourPort), username, password));
  delay(100);
  sendToCamera(camera_ip, deactivateVirtualPort (recordPort), username, password);

while(1){
  
}
  // Try to connect the WiFi network as long as the connection is down
  while (!checkConnection()) {
    Serial.println("Wifi connection is down");
    connectWifi(esp_ip, dns, gateway, subnet, ssid, password);
  }
}


