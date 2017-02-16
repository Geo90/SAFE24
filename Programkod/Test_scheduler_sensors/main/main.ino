/*
    Main
*/
#include "Tasks.h"

TaskPIR taskPIR;

void setup() {
  Serial.begin(115200);
  Serial.print("ESP8266 SETUP");
  Serial.println();
  myNewTask(&taskPIR);  // add task to the list
  startTasks();           // start task
  Serial.println();
}

void loop() {
  //...
}
  


