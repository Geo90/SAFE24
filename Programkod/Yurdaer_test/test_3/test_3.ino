

/*
    Simple HTTP get webclient test
*/
#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include "manageCamera.h"

const char ssid[]     = "3Com";
const char password[] = "14531453";
const char camera_ip[] = "192.168.0.70";
int httpPort = 80;

//The esp module IP, gateway and subnet adresses
IPAddress esp_ip (192, 168, 0, 21);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // We start by connecting to a WiFi network
  connectWifi(esp_ip, gateway, subnet, ssid, password);
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  
  Serial.print("connecting to ");
  Serial.println(camera_ip);
  
  //If connection not successful
  if (!client.connect(camera_ip, httpPort)) {
    Serial.println("connection failed");
  }
}


