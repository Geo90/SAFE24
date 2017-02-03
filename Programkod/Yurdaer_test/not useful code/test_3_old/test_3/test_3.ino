

/*
    Simple HTTP get webclient test
*/

#include <ESP8266WiFi.h>


const char* ssid     = "TP-LINK_7B0E";
const char* password = "23263345";
const char* camera_ip = "192.168.0.70";
const int httpPort = 80;

IPAddress esp_ip (192, 168, 0, 21);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  connectWifi(ssid, password);
}

void loop() {
  delay(2000);
  Serial.print("connecting to ");
  Serial.println(camera_ip);
  WiFiClient client;
  if (!client.connect(camera_ip, httpPort)) {
    Serial.println("connection failed");
  }
  Serial.println (sentToCamera(client, moveCamera(20, 1), camera_ip));
}


void connectWifi(const char ssid[], const char password[]) {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  if (sizeof(password) != 1) {
    WiFi.begin(ssid, password);
    WiFi.config(esp_ip, gateway, subnet);
  }
  else {
    WiFi.begin(ssid);
    WiFi.config(esp_ip, gateway, subnet);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


String sentToCamera ( WiFiClient client, String command, String camera_ip ) {
  String http_response = "";
  // This will send the request to the server
  client.print(String("GET ")
               + command + " HTTP/1.1\r\n"
               +  "Host: "
               + camera_ip
               + "\r\n"
               +  "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 2000) {
      Serial.println("Client Timeout!");
      client.stop();
      timeout = 0;
      break;
    }
    timeout = 1;
  }
  // Read all the lines of the reply from server and print them to Serial
  if (timeout) {
    while (client.available()) {
      http_response = client.readStringUntil('\r');

    }
  }
  return http_response;
}

String moveCamera (int angel, int camera_no) {
  String url = "/axis-cgi/com/ptz.cgi?rpan=" + String(angel) + "&camera=" + String(camera_no);
  return url;
}

