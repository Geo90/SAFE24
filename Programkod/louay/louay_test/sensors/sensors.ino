#include <Ethernet.h>
#include <ESP8266WiFi.h>

const int sensorPin = A0; // 
const int ledPin1 = 14; // 

const int ledPin2 = 12;
const int pir = 13;
unsigned long prevTime;
unsigned long passTime;

int sensorValue = 0; //value read from the PIR sensor
int pirCounter = 0; //what does this count?
int pirSum = 0; //waht is this


/**
 * Initializing the pins
 */
void setup() 
{
  pinMode(ledPin1, OUTPUT); //pin1
  pinMode(ledPin2, OUTPUT); //pin1
  pinMode(pir, INPUT);
  pinMode(sensorPin, INPUT);
  prevTime = passTime = 0;
  Serial.begin(115200);
}


void doWithPirValue(int pirvalue) {
  if (pirvalue == HIGH ){
    //digitalWrite(ledPin1, HIGH);
    pirCounter = pirCounter + 1;
    pirSum = pirSum + 10;
  }

  
  if (pirvalue == LOW ){
    //digitalWrite(ledPin1, LOW);
    pirCounter = pirCounter + 1;
  }
}

void doWhenMove() {
  if (pirCounter == 7) {
    pirCounter = 0;
    if (pirSum == 70) {
      prevTime = millis();
      digitalWrite(ledPin1, HIGH);
      passTime = 0;
    }
    if (pirSum < 70 && ( millis()  - prevTime ) > 10000 ) {
      digitalWrite(ledPin1, LOW);
      prevTime = 0;
      passTime = 0;
    }
    pirSum = 0;
  }  
}

void doWithSensorValue(int sensorvalue) {
  if (sensorvalue > 75) {
      digitalWrite(ledPin2, HIGH);
  }
  if (sensorvalue < 75) {
      digitalWrite(ledPin2, LOW);
  }
}

void loop() 
{ 
  Serial.begin(9600);
  int pirValue = digitalRead(pir);
  delay(10);
  Serial.println(pirValue);
  int sensorValue = analogRead(sensorPin);
  delay(10);
  Serial.println(sensorValue);
  
  doWithSensorValue(sensorValue);
  doWithPirValue(pirValue);
  doWhenMove();
  delay(500);
}

