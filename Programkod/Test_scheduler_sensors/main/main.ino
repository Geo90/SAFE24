
/*
    Main
*/
#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include "manageCamera.h"
#include "schedule.h"

const char* ssid     = "TP-LINK_7B0E";
const char* passwordWifi = "23263345";
const String camera_ip = "192.168.0.70";
const String portStationOne = "8";
const String portRecord = "9";
const String portHome = "10";
const char* username = "root";
const char* password = "pass";


void loop() {
  //...
}



/*
   ----------------------------------------
     Task: Pirsensor
   ----------------------------------------
*/

class PirTask : public Task {
  public:

    const int pirLed = 14; // Big lamp
    const int pirSen = 13; //  Pir sensor

    int pirCounter = 0; // counter to read from pir sensor
    int pirSum = 0; // sum to add up the HIGHs and LOWs from pir sensor
    unsigned long prevTime = 0; // variable that keeps track of a previous time


    void setup() {
      pinMode(pirLed, OUTPUT);
      pinMode(pirSen, INPUT);
    }

    void loop() {
      int pirValue = digitalRead(pirSen);
      delay(10);
      Serial.println(pirValue);
      delay(100);
      doWithPirValue(pirValue);
      doWhenMove();
      delay(390);

    }

    /*
      uses a reading from pir sensor to calculate a movement
    */
    void doWithPirValue(int pirvalue) {
      if (pirvalue == HIGH) {
        pirCounter = pirCounter + 1;
        pirSum = pirSum + 10;
      }

      if (pirvalue == LOW) {
        pirCounter = pirCounter + 1;
      }
    }

    /*
      checks if there is a movement or not and acts according to that
    */
    void doWhenMove() {
      if (pirCounter == 7) {
        pirCounter = 0;
        if (pirSum == 70) {
          prevTime = millis();
          digitalWrite(pirLed, HIGH);

        }
        if (pirSum < 70 && ( millis()  - prevTime ) > 10000 ) {
          digitalWrite(pirLed, LOW);
          prevTime = 0;
        }
        pirSum = 0;
      }
    }

} pirTask;

//----------------------------- END OF PirTask -------------------------------------

/*
   ----------------------------------------
     Task: LedTask
   ----------------------------------------
*/

class LedTask : public Task {
  public:

    const int micLed = 12; // small lamp
    const int micSen = A0; // Analogpin for the pir sensor
    unsigned long previousMillis = 0;
    int timeValue = 0;
    int cameraFlag = 0;


    void setup() {
      pinMode(micSen, INPUT);
      pinMode(micLed, OUTPUT);
    }

    void loop() {
      int sensorValue = analogRead(micSen);
      delay(100);
      Serial.println(sensorValue);
      doWithSensorValue(sensorValue);
      delay(100);
      if (cameraFlag) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= 1000) {
          previousMillis = currentMillis;
          timeValue++;
        }
        if (timeValue == 15) {
          moveCamera();
        }
        if (timeValue == 40) {
          returnStationOne();
        }
        if (timeValue == 60) {
          returnHome();
          cameraFlag = 0;
          timeValue = 0;
        }
      }
    }

    /*
      checks if the sensor value goes past the threshold of 75.
    */
    void doWithSensorValue(int sensorvalue) {
      if (sensorvalue > 71) { // LED ON
        digitalWrite(micLed, HIGH);
        activateCamera();
        cameraFlag = 1;
        timeValue = 0;
      }
      if (sensorvalue <= 71) { // LED OFF
        digitalWrite(micLed, LOW);
      }
    }

} ledTask;

//----------------------------- END OF ledTask -------------------------------------

/*
   ----------------------------------------
     Task: WifiTask
   ----------------------------------------
*/

class WifiTask : public Task {
  public:

    void setup() {
      //...
    }

    void loop() {
      // Try to connect the WiFi network as long as the connection is down
      while (!checkConnection()) {
        Serial.println("Wifi connection is down");
        connectWifi(ssid, password);
      }
    }
} WifiTask;


void setup() {

  Serial.begin(115200);
  delay(100);

  // Connecting to a WiFi network
  connectWifi(ssid, passwordWifi);
  delay(100);
  setHostInfo( camera_ip, username, password, portStationOne, portRecord, portHome);
  Scheduler.start(&WifiTask);
  Scheduler.start(&pirTask);
  Scheduler.start(&ledTask);
  Scheduler.begin();
}


