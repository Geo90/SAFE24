#include "Task1.h" 


//--------------------------------------------------
//-------------------- TASK 1 ----------------------
//--------------------------------------------------

void Task1::setup() // :: => "binary scope resolution operator", setup() is a member of the class task1
{
  Task1::led_1 = 12;
  pinMode(led_1, OUTPUT);
}

void Task1::loop()
{
  Serial.print(" TASK_1... ");
  digitalWrite(led_1, HIGH);
  delay(5000);
  digitalWrite(led_1, LOW);
  delay(5000);
}
