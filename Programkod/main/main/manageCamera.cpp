/*
  ConnectToWiFi.h
  Contains fuctions that kan be used for comminication
  between httpclient (ESP8266) and httphost (Axis IP-Camera) 
  Created by SAFE24, February 18, 2017.
  Released into the public domain.
*/


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "manageCamera.h"


/**
   This function will send a request to the server (Axis IP-Camera)
*/
int sendToCamera ( String host, String command, const char username[], const char password[]) {
  int check;
  HTTPClient httpClient;
  String http_response;
  Serial.print("Connecting to ");
  Serial.println(host);
   // start connection and send HTTP header
  httpClient.begin("http://" + host + command);
   // Authorization
  httpClient.setAuthorization(username, password);
  int httpCode = httpClient.GET();
  // httpCode will be negative when error occurs
  if (httpCode > 0) {
    check = 1;

    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      http_response =  httpClient.getString();
      Serial.println(http_response);
    }
  }
  //If connection not successful
  else {
    http_response = "connection failed";
    check = 0;
  }
  httpClient.end();
  return check;
}

/*Continuous pan/tilt motion.
  Positive values mean right (pan) and up (tilt),
  negative values mean left (pan) and down (tilt).
  "0,0" means stop.
*/
String continuousPanTiltMove (int panSpeed, int tiltSpeed, int camera_no) {
  String url = "/axis-cgi/com/ptz.cgi?continuouspantiltmove=" + String(panSpeed) + "," + String(tiltSpeed) + "&camera=" + String(camera_no);
  return url;
}


//  Activates a virtual port on Camera
String activateVirtualPort (String portNumber) {
  String url = "/axis-cgi/virtualinput/activate.cgi?schemaversion=1&port=" + portNumber;
  return url;
}

//  Deactivates a virtual port on Camera
String deactivateVirtualPort (String portNumber) {
  String url = "/axis-cgi/virtualinput/deactivate.cgi?schemaversion=1&port=" + portNumber;
  return url;
}





