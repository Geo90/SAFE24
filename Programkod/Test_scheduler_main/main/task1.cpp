//#include "test_schedule.h"

#include "task1.h"



//--------------------------------------------------
//----- TASK 1 -----
//--------------------------------------------------


const int led_1 = 12;

setup::setup()
{
  pinMode(led_1, OUTPUT);
}

loop::loop()
{
  Serial.print(" LED_1 TASK ");
  digitalWrite(led_1, HIGH);
  delay(5000);
  digitalWrite(led_1, LOW);
  delay(5000);
}
