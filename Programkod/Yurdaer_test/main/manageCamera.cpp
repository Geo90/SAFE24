

#include <ESP8266HTTPClient.h>
#include "manageCamera.h"
/**
   This function will send a request to the server
*/
String sendToCamera ( String host, String command) {
  HTTPClient httpClient;
  String http_response;
  Serial.print("connecting to ");
  Serial.println(host);
  httpClient.begin("http://" + host + command); //HTTP
  Serial.println("[HTTP] GET...\n");
  int httpCode =  httpClient.GET();


  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    //  if (httpCode == HTTP_CODE_OK) {
    http_response =  httpClient.getString();
    //    }
  }
  
  //If connection not successful
  else {
    http_response = "connection failed";
  }
  
  httpClient.end();
  return http_response;
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





