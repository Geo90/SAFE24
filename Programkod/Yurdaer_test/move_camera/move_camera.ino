/**
 * Does not manouver the camera but just establishes a
 * WiFi-connection the the host ssid.
 */
#include <ESP8266WiFi.h>

//Connect to the host(router) 3Com
const char* ssid     = "3Com";
const char* password = "";

//IP-adress of the camera
const char* camera_ip= "192.168.0.70";

//The ESP IP, gateway, subnet and DNS
IPAddress ip = (192,168,0,21);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 249);

/**
 * Establishes a connection to the WiFi-network
 */
void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  //Connecting to WiFi network
  WiFi.begin(ssid, password);

  //Waiting for acknowledgement from host for successful connection 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If successful connection established printout 
  //local IP-adress
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println("192.168.0.70");


  // URL pan-request for the Camera
  String url = "http://192.168.0.70/axis-cgi/com/ptz.cgi?rpan=10&camera=1";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server1  client.print(String("POST") + url);
  delay(10);

  //Reads and prints reply from the Camera-server
  Serial.println("Response: ");
  while(client.available()){
     String line = client.readStringUntil('\r');
     Serial.print(line);
  }

  //Connection alwas closes automatically after request and response are done
  Serial.println();
  Serial.println("closing connection");
}
