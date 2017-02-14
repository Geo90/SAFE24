
#include "test_schedule.h"


//Creates a new task and adds it to the scheduler
void myNewTask( Task *task ) //Task* func, void func(void), void myNewTask( void (*f) )
{  
  Serial.println();
  Serial.print("Adding task to list...");
  Serial.println();
  Scheduler.start( task ); 
}

//Starts all the tasks in the scheduler
void startTasks(void){
  Scheduler.begin();
}

