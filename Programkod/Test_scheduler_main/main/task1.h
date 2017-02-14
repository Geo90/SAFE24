#ifndef task1_h // In order to tell the compiler that it will only be defined once we need these guards
#define task1_h



//#include <Scheduler.h> // needs to be included in order to know about the Task header
#include "schedule.h"



class task1 : public Task 
{
  public:
    int led_1;
    void setup(void);
    void loop(void);
} led1_task;




#endif

