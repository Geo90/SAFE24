
#include "test_schedule.h"


//Creates a new task and adds it to the scheduler
void myNewTask(Task* func){
  Serial.println();
  Serial.print("Adding tsdk to list...");
  Scheduler.start(func);
}

//Starts all the tasks in the scheduler
void startTasks(void){
  Scheduler.begin();
}

