#include <Ethernet.h>
#include <ESP8266WiFi.h>

const int sensorPin = A0; // Analogpin for the pir sensor 
const int ledPin1 = 14; // Big lamp 
const int ledPin2 = 12; // Small lamp
const int pir = 13; //  Pir sensor
unsigned long prevTime; // variable that keeps track of a previous time 

int sensorValue = 0; // value read from the PIR sensor
int pirCounter = 0; // counter to read from pir sensor
int pirSum = 0; // sum to add up the HIGHs and LOWs from pir sensor

/**
 * Initializing the pins
 */
void setup() 
{
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
  pinMode(pir, INPUT);
  pinMode(sensorPin, INPUT);
  prevTime = 0;
  Serial.begin(115200);
}

/*
 * uses a reading from pir sensor to calculate a movement
 */
void doWithPirValue(int pirvalue) {
  if (pirvalue == HIGH){
    pirCounter = pirCounter + 1;
    pirSum = pirSum + 10;
  }

  if (pirvalue == LOW){
    pirCounter = pirCounter + 1;
  }
}

/*
 * checks if there is a movement or not and acts according to that
 */
void doWhenMove() {
  if (pirCounter == 7) {
    pirCounter = 0;
    if (pirSum == 70) {
      prevTime = millis();
      digitalWrite(ledPin1, HIGH);
    }
    if (pirSum < 70 && ( millis()  - prevTime ) > 10000 ) {
      digitalWrite(ledPin1, LOW);
      prevTime = 0;
    }
    pirSum = 0;
  }  
}

/*
 * checks if the sensor value goes past the threshold of 75. 
 */
void doWithSensorValue(int sensorvalue) {
  if (sensorvalue > 75) { // LED ON 
      digitalWrite(ledPin2, HIGH);
  }
  if (sensorvalue < 75) { // LED OFF
      digitalWrite(ledPin2, LOW);
  }
}

/*
 * loops continously in order to obtain the newest sensor values  
 */
void loop() 
{ 
  Serial.begin(115200);
  int pirValue = digitalRead(pir);
  delay(10);
  Serial.println(pirValue);
  int sensorValue = analogRead(sensorPin);
  delay(100);
  Serial.println(sensorValue);
  
  doWithSensorValue(sensorValue);
  doWithPirValue(pirValue);
  doWhenMove();
  delay(390);
}

