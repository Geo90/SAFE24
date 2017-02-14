//#include "test_schedule.h"
#include "task1.h" //this file (task1.cpp) includes scheduler.h because task1.h includes <Scheduler.h> 



//--------------------------------------------------
//----- TASK 1 -----
//--------------------------------------------------


void task1::setup() // :: => "binary scope resolution operator", setup() is a member of the class task1
{
  const int led_1 = 12;
  pinMode(led_1, OUTPUT);
}

void task1::loop()
{
  Serial.print(" LED_1 TASK ");
  digitalWrite(led_1, HIGH);
  delay(5000);
  digitalWrite(led_1, LOW);
  delay(5000);
}
