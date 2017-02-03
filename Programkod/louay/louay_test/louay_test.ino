/**
 * 
 */

#include <Ethernet.h>
#include <ESP8266WiFi.h>

//Defining ESP8266 pins
const int sensorPin = A0; // 
const int ledPin1 = 14; // 
const int pirPin = 16;
const int ledPin2 = 13;

//Sensor values and variables
int sensorValue = 0;
int pirCounter = 0;
int pirSum = 0;

//EthernetClient object and specified Host with password
EthernetClient client;
const char* ssid     = "Tele2GatewayE2B2";
const char* password = "59b3239n";


/**
 * Initializing the pins
 */
void setup() 
{

  pinMode(ledPin1, OUTPUT); //pin1
  pinMode(ledPin1, OUTPUT); //pin1
  pinMode(pirPin, INPUT);   //pirPin
  Serial.begin(115200);
}

/**
 * 
 */
void loop() 
{
  //This is being resetted everytime the loop starts (Why?)
  digitalWrite(ledPin1, LOW);

  //Reading what? Shock?
  sensorValue = analogRead(sensorPin);
  delay(99);

  //Shock is detected and LED lights up 
  int pirValue = digitalRead(pirPin);
  if (pirValue == HIGH ){
    digitalWrite(ledPin2, HIGH);
    pirCounter = pirCounter + 1;
    pirSum = pirSum + 10;
  }

  //No shock detected LED is switched off
  if (pirValue == LOW ){
    digitalWrite(ledPin2, LOW);
    pirCounter = pirCounter + 1;
  }

  //What is happening here?
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

  //What is happening here?
  if (sensorValue > 75) {
      Serial.println(sensorValue);
      digitalWrite(ledPin1, HIGH);
      String url = "http://192.168.0.70/axis-cgi/com/ptz.cgi?rpan=10&camera=3";
  }
}
