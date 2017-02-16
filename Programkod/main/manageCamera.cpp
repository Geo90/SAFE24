
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "manageCamera.h"
/**
   This function will send a request to the server
*/
int sendToCamera ( String host, String command,const char username[],const char password[]) {
  int check;
  HTTPClient httpClient;
  String http_response;
  Serial.print("Connecting to ");
  Serial.println(host);
  httpClient.begin("http://" + host + command);
  httpClient.setAuthorization(username, password);
  // start connection and send HTTP header
  int httpCode = httpClient.GET();
  // httpCode will be negative on error
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




