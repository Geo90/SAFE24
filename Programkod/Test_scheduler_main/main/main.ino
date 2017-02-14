/*
    Main
*/

#include <ESP8266WiFi.h>
#include "task1.h"
#include "test_schedule.h"


void setup() {
  Serial.begin(115200);
  Serial.print("ESP8266 SETUP");
  Serial.println();
  myNewTask(&led1_task);
  Serial.println();
}


void loop() {
  //...
}
  


