
/*
    Main
*/
#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include "manageCamera.h"
#include <Scheduler.h>

//Information about the IP-camera
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
     Task: PIR-sensor
   ----------------------------------------
*/

class PirTask : public Task {
  public:

    const int pirLed = 14;      // Big lamp
    const int pirSen = 13;      //  Pir sensor

    int pirCounter = 0;         // counter to read from pir sensor
    int pirSum = 0;             // sum to add up the HIGHs and LOWs from pir sensor
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
      Uses the reading from the PIR-sensor to calculate a movement
      Reurns an integer with value 0 if no movement is detected or
      the value 1 if movement is detected
    */
    int doWithPirValue(int pirvalue) {
      int movement = 0; //no movement
      if (pirvalue == HIGH) {
        //Movement detected
        pirCounter = pirCounter + 1;
        pirSum = pirSum + 10;
        movement = 1;
      }

      if (pirvalue == LOW) {
        //No movement detected
        pirCounter = pirCounter + 1;
      }
    }

    /*
      Checks if there is a movement or not and acts according to that
      Reurns an integer with value 0 if no movement is detected or
      the value 1 if movement is detected
    */
    int doWhenMove() {
      int movement = 0; //no movement
      if (pirCounter == 7) {
        pirCounter = 0;
        if (pirSum == 70) {
          //Movement detected
          prevTime = millis();
          digitalWrite(pirLed, HIGH);
          movement = 1;
        }
        if (pirSum < 70 && ( millis()  - prevTime ) > 10000 ) {
          //No movement detected
          digitalWrite(pirLed, LOW);
          prevTime = 0;      
        }
        pirSum = 0;
      }
    return movement;
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
      Checks if the sensor value goes past the threshold value 75.
      Reurns an integer with value 0 if no movement is detected or
      the value 1 if movement is detected
    */
    int doWithSensorValue(int sensorvalue) {
      int movement = 0; //no movement detected
      if (sensorvalue > 71) { // LED ON
        //Movement detected
        digitalWrite(micLed, HIGH);
        activateCamera();
        cameraFlag = 1;
        timeValue = 0;
        movement = 1;
      }
      if (sensorvalue <= 71) { // LED OFF
        //No movement detected
        digitalWrite(micLed, LOW);
      }
      return movement;
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

  //Start all the tasks
  Scheduler.start(&WifiTask);
  Scheduler.start(&pirTask);
  Scheduler.start(&ledTask);
  Scheduler.begin();
}


