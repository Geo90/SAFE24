#ifndef Task2_h // tellS the compiler that it will only be defined once
#define Task2_h

#include "SchedulerT.h" // needs to be included in order to know about the Task.h (public Task)


class Task2 : public Task 
{
  
  public:
    int led_2;
    void setup(void);
    void loop(void);
    
};

extern Task2 led2_task; // extern is needed to avoid multiple definitions 


#endif

