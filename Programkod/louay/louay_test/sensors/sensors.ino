#include <Ethernet.h>
#include <ESP8266WiFi.h>

/*
 * Declaring the pins required for pir sensor
 */
const int pirLed = 14; // Big lamp for pir-action
const int pirSen = 13; // Digital pin for pir sensor


/*
 * Declaring variables used for pir-action
 */
unsigned long prevTime; // variable that keeps track of a previous time 
int pirCounter = 0; // counter to read from pir sensor
int pirSum = 0; // sum to add up the HIGHs and LOWs from pir sensor


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
  if (pirCounter == 8) {
    pirCounter = 0;
    if (pirSum == 0) {
      prevTime = millis();
      digitalWrite(pirLed, HIGH);
    }
    if (pirSum < 80 && ( millis()  - prevTime ) > 10000 ) {
      digitalWrite(pirLed, LOW);
      prevTime = 0;
    }
    pirSum = 0;
  }  
}



/*
 * Initializing the pins required for mic sensor
 */
const int micSen = A0; // Analogpin for the pir sensor 
const int micLed = 12; // Small lamp for mic-action

/*
 * Declaring variables used for mic-action
 */
int sensorValue = 0; // value read from the PIR sensor


/*
 * checks if the sensor value goes past the threshold of 71. 
 */
void doWithSensorValue(int sensorvalue) {
  if (sensorvalue > 71) { // LED ON 
      digitalWrite(micLed, HIGH);
  }
  if (sensorvalue < 72) { // LED OFF
      digitalWrite(micLed, LOW);
  }
}


/**
 * Initializing setup-options for pir and mic-action
 */
void setup() 
{
  pinMode(pirLed, OUTPUT); 
  pinMode(micLed, OUTPUT); 
  pinMode(pirSen, INPUT);
  pinMode(micSen, INPUT);
  prevTime = 0;
  Serial.begin(115200);
}


/*
 * loops continously in order to obtain the newest sensor values  
 * Note that the pirSen gets an digitalWrite of LOW before reading
 * Delaays are calculated according to the reading values from pir sensor
 */
void loop() 
{ 
  Serial.begin(115200);
  digitalWrite(pirSen, LOW); // to be noted
  int pirValue = digitalRead(pirSen);
  delay(10);
  Serial.println(pirValue);
  int sensorValue = analogRead(micSen);
  delay(100);
  Serial.println(sensorValue);
  
  doWithSensorValue(sensorValue);
  doWithPirValue(pirValue);
  doWhenMove();
  delay(390);
}

