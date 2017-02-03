

#include <ESP8266WiFi.h>

/**
 * This function will send a request to the server
 */
String sendToCamera (WiFiClient client, String command, String camera_ip ) {
  //Send string command to the specified camera_ip
  client.print(String("GET ")
               + command + " HTTP/1.1\r\n"
               +  "Host: "
               + camera_ip
               + "\r\n"
               +  "Connection: close\r\n\r\n");
  
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String http_response = client.readStringUntil('\r');
    return http_response;
  }
}

String moveCamera(int angle){
  String moveCamera(angle, 0);
}

/**
 * Controlling the camera movement by passing in int arguments for the desired angle
 * as int and the camera number as int.
 */
String moveCamera (int angle, int camera_no) {
    String url = "/axis-cgi/com/ptz.cgi?rpan=" + String(angle) + "&camera=" + String(camera_no);
    return url;
  }
