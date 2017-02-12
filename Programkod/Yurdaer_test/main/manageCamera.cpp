
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "manageCamera.h"
/**
   This function will send a request to the server
*/
int sendToCamera ( String host, String command) {
  int check;
  HTTPClient httpClient;
  String http_response;
  Serial.print("Connecting to ");
  Serial.println(host);
  httpClient.begin("http://" + host + command);
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

/**
   Controlling the camera movement by passing in int arguments for the desired angle
   as int and the camera number as int.
*/
String moveCameraHorizontal (int angle, int camera_no) {
  String url = "/axis-cgi/com/ptz.cgi?rpan=" + String(angle) + "&camera=" + String(camera_no);
  return url;
}

String moveCameraVertical (int angle, int camera_no) {
  String url = "/axis-cgi/com/ptz.cgi?rtilt=" + String(angle) + "&camera=" + String(camera_no);
  return url;
}

String autoFocus (String OnOff, String camera_no) {
  String url = "/axis-cgi/com/ptz.cgi?autofocus=" + OnOff + "&camera=" + String(camera_no);
  return url;
}

String autoIris (String OnOff, String camera_no) {
  String url = "/axis-cgi/com/ptz.cgi?autoiris=" + OnOff + "&camera=" + String(camera_no);
  return url;
}

/*Continuous pan/tilt motion.
  Positive values mean right (pan) and up (tilt),
  negative values mean left (pan) and down (tilt). "0,0"
  means stop.
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

//
int setAuthorization(String hostIp, const char* username, const char* password) {
  int check;
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");

  // start connection and send HTTP header
  http.begin("http://" + hostIp);
  http.setAuthorization(username, password);

  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    check = 1;

    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      Serial.println(response);

    }
  } else {
    Serial.printf("[HTTP] Authorization failed, error: %s\n", http.errorToString(httpCode).c_str());
    check = 0;
  }

  return check;
}



