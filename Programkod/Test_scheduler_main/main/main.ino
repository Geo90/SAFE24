/*
    Main
*/
#include "Task1.h"
#include "Task2.h"

Task1 led1_task;
Task2 led2_task;

void setup() {
  Serial.begin(115200);
  Serial.print("ESP8266 SETUP");
  Serial.println();
  myNewTask(&led1_task);  // add task to the list
  myNewTask(&led2_task);  // add task to the list
  startTasks();           // start task
  Serial.println();
}

void loop() {
  //...
}
  


