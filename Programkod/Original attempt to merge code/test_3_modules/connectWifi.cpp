

#include <ESP8266WiFi.h>
#include "connectWiFi.h"


void connectWifi(IPAddress esp_ip, IPAddress gateway, IPAddress subnet, const char ssid[], const char password[]) {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  if (sizeof(password) != 1) {
    WiFi.begin(ssid, password);
    WiFi.config(esp_ip, gateway, subnet);
  }
  else {
    WiFi.begin(ssid);
    WiFi.config(esp_ip, gateway, subnet);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

