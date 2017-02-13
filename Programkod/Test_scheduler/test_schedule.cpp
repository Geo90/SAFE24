
#include "test_schedule.h"


//Creates a new task and adds it to the scheduler
void myNewTask(Task* func){
  Serial.println();
  Serial.print("This is a template for further development of modules for the project");
  Scheduler.start(func);
}

//Starts all the tasks in the scheduler
void startTasks(void){
  Scheduler.begin();
}

