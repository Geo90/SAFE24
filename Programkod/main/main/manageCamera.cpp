
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "manageCamera.h"

String camera_ip;
const char* Username;
const char* Password;
String portStationOne;
String portRecord;
String portHome;

/**
   This function will send a request to the server
*/
int sendToCamera ( String host, String command, const char username[], const char password[]) {
  int check;
  HTTPClient httpClient;
  String http_response;
  Serial.print("Connecting to ");
  Serial.println(host);
  httpClient.begin("http://" + host + command);
  httpClient.setAuthorization(username, password);
  // start connection and send HTTP header
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

/*
 * SET: the connection data is stored in this class for future use when connecting to the IP-camera
 */
void setHostInfo(String hostIp, const char hostUsername[], const char hostPassword[], String portStation, String portRecord, String portHome) {
  camera_ip = hostIp;
  Username = hostUsername;
  Password = hostPassword;
  portStationOne = portStation;
  portRecord = portRecord;
  portHome = portHome;

}


void activateCamera() {
  sendToCamera(camera_ip, activateVirtualPort (portStationOne), Username, Password);
  delay(10);
  sendToCamera(camera_ip, activateVirtualPort (portRecord), Username, Password);
  delay(10);
  sendToCamera(camera_ip, deactivateVirtualPort (portRecord), Username, Password);
  delay(10);
  sendToCamera(camera_ip, deactivateVirtualPort (portStationOne), Username, Password);
}

void moveCamera() {
  sendToCamera(camera_ip, continuousPanTiltMove (9, 0, 1), Username, Password);
}

void returnStationOne() {
  sendToCamera(camera_ip, activateVirtualPort (portStationOne), Username, Password);
  delay(10);
  sendToCamera(camera_ip, deactivateVirtualPort (portStationOne), Username, Password);
}

void returnHome() {
  sendToCamera(camera_ip, activateVirtualPort (portHome), Username, Password);
  delay(10);
  sendToCamera(camera_ip, deactivateVirtualPort (portHome), Username, Password);
}


