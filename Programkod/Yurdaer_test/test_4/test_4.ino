
 

/*
    Simple HTTP get webclient test
*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "connectWiFi.h"
#include "manageCamera.h"
#include "schedule.h"
#include <Arduino.h>
const char* ssid     = "TP-LINK_7B0E";
const char* password = "23263345";
const String camera_ip = "192.168.0.70";
const String time_host ="www.google.com";


//The esp module IP, gateway and subnet adresses
IPAddress esp_ip (192, 168, 0, 21);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(195, 178, 231, 5);

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // We start by connecting to a WiFi network
  connectWifi(esp_ip,dns, gateway, subnet, ssid, password);
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
 Serial.println( sendToCamera(GetTimeCamera(),camera_ip));

//Serial.print( sendToCamera(continuousPanTiltMove(0,0,1),camera_ip));
//Serial.println( sendToCamera("",time_host));
  
 delay(2000);
}


