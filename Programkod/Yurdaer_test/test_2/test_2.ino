

/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266WiFi.h>
 
const char* ssid     = "3Com";
const char* password = "14531453";
const char* host_camera ="192.168.0.70";
 IPAddress static_ip (192, 168, 0, 21);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid);
   WiFi.config(static_ip,gateway,subnet);
  
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
  delay(500);
  ++value;
 
  Serial.print("connecting to ");
  Serial.println(host_camera);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host_camera, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
   String url = "/axis-cgi/com/ptz.cgi?rpan=3&camera=1";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host_camera + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(50);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
