
#include <ESP8266WiFi.h>
#include "connectWiFi.h"

/**
   Function that establishes a connection to the specified host
*/
void connectWifi(IPAddress esp_ip, IPAddress dns, IPAddress gateway, IPAddress subnet, const char ssid[], const char password[]) {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //Checks if password needed of not and connects to the host
  if (sizeof(password) != 1) {
    WiFi.begin(ssid, password);
    // WiFi.config(esp_ip,dns, gateway, subnet);
  }
  else {
    WiFi.begin(ssid);
    //  WiFi.config(esp_ip,dns, gateway, subnet);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int checkConnection(){
  if(WiFi.status() == WL_CONNECTED){
  return 1;
  }
    else
  {
  return 0;
}
}

