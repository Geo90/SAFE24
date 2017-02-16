#ifndef Tasks_h // tellS the compiler that it will only be defined once
#define Tasks_h

#include "SchedulerT.h" // needs to be included in order to know about the Task.h (public Task)


class TaskPIR : public Task 
{
  
  public:
    
	// Variables
	int sensorPin;
	int ledPin1;
	int ledPin2;
	int pir;
	unsigned long prevTime;
	int sensorValue;
	int pirCounter;
	int pirSum;
	
	// Methods
    void setup(void);
    void loop(void);
    void doWithPirValue(int);
    void doWhenMove();
    
};


/*class TaskLAMP : public Task 
{
  
  public:
    int led_1;
    void setup(void);
    void loop(void);
    
};
*/


extern TaskPIR taskPIR; // extern is needed to avoid multiple definitions 
//extern TaskLAMP taskLAMP;

#endif
