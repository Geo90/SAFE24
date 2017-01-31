

#include <ESP8266WiFi.h>

String sentToCamera (WiFiClient client, String command, String camera_ip ) {
  // This will send the request to the server
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

  String moveCamera (int angel, int camera_no) {
    String url = "/axis-cgi/com/ptz.cgi?rpan=" + String(angel) + "&camera=" + String(camera_no);
    return url;
  }
