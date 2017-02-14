/*
    Main
*/
//#include "test_schedule.h"
#include "task1.h"



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
  


