#include <Ethernet.h>
#include <ESP8266WiFi.h>

int sensorPin = A0; // 
int ledPin1 = 14; // 
int pirPin = 16;
int ledPin2 = 13;

int sensorValue = 0;
int pirCounter = 0;
int pirSum = 0;

EthernetClient client;
const char* ssid     = "Tele2GatewayE2B2";
const char* password = "59b3239n";



void setup() 
{

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(115200);
}

void loop() 
{
  digitalWrite(ledPin1, LOW);
  sensorValue = analogRead(sensorPin);
  delay(99);
  int pirValue = digitalRead(pirPin);
  if (pirValue == HIGH ){
    digitalWrite(ledPin2, HIGH);
    pirCounter = pirCounter + 1;
    pirSum = pirSum + 10;
  }
  if (pirValue == LOW ){
    digitalWrite(ledPin2, LOW);
    pirCounter = pirCounter + 1;
  }

  if (pirCounter == 5) {
    pirCounter = 0;
    if (pirSum > 30) {
      digitalWrite(ledPin2, HIGH);
    }
    if (pirSum < 30) {
      digitalWrite(ledPin2, LOW);
    }
    pirSum = 0;
  }
  delay(5);
  if (sensorValue > 75) {
      Serial.println(sensorValue);
      digitalWrite(ledPin1, HIGH);
      String url = "http://192.168.0.70/axis-cgi/com/ptz.cgi?rpan=10&camera=3";
  }
}
