

/*
    Simple HTTP get webclient test
*/

#include <ESP8266WiFi.h>

const char ssid[]     = "3Com";
const char password[] = "14531453";
const char camera_ip[] = "192.168.0.70";
const int httpPort = 80;

IPAddress esp_ip (192, 168, 0, 21);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  connectWifi(ssid, password);
  /*
    WiFi.begin(ssid);
    WiFi.config(esp_ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("");
  */
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());






}


void loop() {
  delay(2000);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(camera_ip);
  if (!client.connect(camera_ip, httpPort)) {
    Serial.println("connection failed");
  }
  moveCamera(client, 20, 1);
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String http_response = client.readStringUntil('\r');
    Serial.print(http_response);
  }

}

void connectWifi(const char ssid[], const char password[]) {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
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
}




void moveCamera (WiFiClient client, int angel, int camera_no) {
  Serial.print("2 ");
  String url = "/axis-cgi/com/ptz.cgi?rpan=" + String(angel) + "&camera=" + String(camera_no);
  // This will send the request to the server
  client.print(String("GET ")
               + url + " HTTP/1.1\r\n"
               +  "Host: "
               + camera_ip
               + "\r\n"
               +  "Connection: close\r\n\r\n");
}

