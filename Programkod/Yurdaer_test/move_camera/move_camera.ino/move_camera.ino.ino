#include <ESP8266WiFi.h>


const char* ssid     = "3Com";
const char* password = "";


const char* camera_ip= "192.168.0.70";
IPAddress ip = (192,168,0,21);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 249);
void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.config(ip,dns,gateway,subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println("192.168.0.70");

  // Use WiFiClient class to create TCP connections
 // WiFiClient client;
//  const int httpPort = 80;
 // if (!client.connect(camera_ip, httpPort)) {
 //   Serial.println("connection failed");
 //   return;
//  }

  // We now create a URI for the request
  String url = "http://192.168.0.70/axis-cgi/com/ptz.cgi?rpan=10&camera=3";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  //client.print(String("POST") + url);
  delay(10);

  // Read all the lines of the reply from server and print them to Serial
//  Serial.println("Respond:");
//  while(client.available()){
 //   String line = client.readStringUntil('\r');
 //   Serial.print(line);
//  }

  Serial.println();
  Serial.println("closing connection");
}
