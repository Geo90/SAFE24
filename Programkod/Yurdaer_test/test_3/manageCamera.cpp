

#include <ESP8266WiFi.h>

/**
 * This function will send a request to the server
 */
String sendToCamera (WiFiClient client, String command,const char* camera_ip, int httpPort ) {
  String http_response;
  Serial.print("connecting to ");
  Serial.println(camera_ip);
  Serial.println("a");
  //If connection not successful
  if (!client.connect(camera_ip, httpPort)) {
    Serial.println("connection failed");
    return http_response="connection failed";
     Serial.println("b");
  }
  
  else{
  //Send string command to the specified camera_ip
  client.print(String("GET ")
               + command + " HTTP/1.1\r\n"
               +  "Host: "
               + camera_ip
               + "\r\n"
               +  "Connection: close\r\n\r\n");
 
  // Read all the lines of the reply from server and print them to Serial
     Serial.println("c");
  while (client.available()) {
    char  response = client.readStringUntil('\r');
     Serial.println(response);
    return http_response;
  }
   }
     Serial.println("d");
    
}
/*
String moveCamera(int angle){
  String moveCamera(angle, 0);
}
*/
/**
 * Controlling the camera movement by passing in int arguments for the desired angle
 * as int and the camera number as int.
 */
String moveCamera (int angle, int camera_no) {
    String url = "/axis-cgi/com/ptz.cgi?rpan=" + String(angle) + "&camera=" + String(camera_no);
    return url;
  }
