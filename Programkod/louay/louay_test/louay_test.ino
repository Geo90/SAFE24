#include <Ethernet.h>
#include <ESP8266WiFi.h>

const int sensorPin = A0; // 
const int ledPin1 = 14; // 
const int pirPin = 16;
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
  pinMode(pirPin, INPUT);   //pirPin
  pinMode(sensorPin, INPUT);
  prevTime = passTime = 0;
  Serial.begin(115200);
}

void loop() 
{ 
  pinMode(pir, INPUT);
  int pirValue = digitalRead(pir);
  Serial.println(pirValue);
  delay(50);

  int sensorValue = analogRead(sensorPin);
  delay(50);                                                                                                                                                                                                                                                              
  if (pirValue == HIGH ){
    //digitalWrite(ledPin1, HIGH);
    pirCounter = pirCounter + 1;
    pirSum = pirSum + 10;
  }
  if (pirValue == LOW ){
    //digitalWrite(ledPin1, LOW);
    pirCounter = pirCounter + 1;
  }
  delay(300);

  if (pirCounter == 7) {
    pirCounter = 0;
    if (pirSum == 70) {
      prevTime = millis();
      digitalWrite(ledPin1, HIGH);
      passTime = 0;
    }
    if (pirSum < 70 && ( millis()  - prevTime ) > 60000 ) {
      digitalWrite(ledPin1, LOW);
      prevTime = 0;
      passTime = 0;
    }
    pirSum = 0;
  }
  delay(100);
  

  if (sensorValue > 75) {
     
      delay(90);
      digitalWrite(ledPin2, HIGH);
  }
  if (pirValue < 75) {
      
      delay(90);
      digitalWrite(ledPin2, LOW);
 
  }
  
}

