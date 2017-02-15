#ifndef Task1_h // tellS the compiler that it will only be defined once
#define Task1_h

#include "SchedulerT.h" // needs to be included in order to know about the Task.h (public Task)


class Task1 : public Task 
{
  public:
    int led_1;
    void setup(void);
    void loop(void);
};


extern Task1 led1_task; // extern is needed to avoid multiple definitions 


#endif

