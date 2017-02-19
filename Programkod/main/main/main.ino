
/*

  This sketch created for ESP8266. Contains three different tasks.
  WifiTask check and creat the WiFi connection.
  pirTask control a PIR sensor.
  micTask control a sound sensor.
  Created by SAFE24, February 18, 2017.
*/
#include <ESP8266WiFi.h>
#include "connectWiFi.h"
#include "manageCamera.h"
#include <Scheduler.h>

//wireless network SSID (name)
const char* ssid     = "TP-LINK_7B0E";
//wireless network password
const char* passwordWifi = "23263345";
//IP-adress for camera
const String camera_ip = "192.168.0.70";
//virtual port numbers on camera
const String portStationOne = "8";
const String portRecord = "9";
const String portHome = "10";
//username and password for camera
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
      return movement;
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

class MicTask : public Task {
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
      // if the camera is activated
      if (cameraFlag) {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= 1000) {
          previousMillis = currentMillis;
          timeValue++;
        }
        //After about 15 seconds starts continuous pan motion with speed 9
        if (timeValue == 15) {
          sendToCamera(camera_ip, continuousPanTiltMove (9, 0, 1), username, password);
        }
        //After about 40 seconds aims the camera to the busstation.
        if (timeValue == 40) {
          sendToCamera(camera_ip, activateVirtualPort (portStationOne), username, password);
          delay(10);
          sendToCamera(camera_ip, deactivateVirtualPort (portStationOne), username, password);
        }
        //After about 60 seconds aims the camera to the homeposition.
        if (timeValue == 60) {
          sendToCamera(camera_ip, activateVirtualPort (portHome), username, password);
          delay(10);
          sendToCamera(camera_ip, deactivateVirtualPort (portHome), username, password);
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
      int soundDetected = 0; //no movement detected
      if (sensorvalue > 71) { // LED ON
        //Movement detected
        digitalWrite(micLed, HIGH);
        //Activates virtuall port 8 aims the cameran to the bustation
        sendToCamera(camera_ip, activateVirtualPort (portStationOne), username, password);
        delay(10);
        //Activates virtuall port 9 that starts recording
        sendToCamera(camera_ip, activateVirtualPort (portRecord), username, password);
        delay(10);
        //Deactivates virtuall port 9
        sendToCamera(camera_ip, deactivateVirtualPort (portRecord), username, password);
        delay(10);
        //Deactivates virtuall port 8
        sendToCamera(camera_ip, deactivateVirtualPort (portStationOne), username, password);
        cameraFlag = 1;
        timeValue = 0;
        soundDetected = 1;
      }
      if (sensorvalue <= 71) { // LED OFF
        //No movement detected
        digitalWrite(micLed, LOW);
      }
      return soundDetected;
    }

} micTask;

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

  //Start all the tasks
  Scheduler.start(&WifiTask);
  Scheduler.start(&pirTask);
  Scheduler.start(&micTask);
  Scheduler.begin();
}

