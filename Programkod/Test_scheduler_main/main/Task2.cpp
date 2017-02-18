#include "Task2.h" 


//--------------------------------------------------
//-------------------- TASK 2 ----------------------
//--------------------------------------------------

void Task2::setup() // :: => "binary scope resolution operator", setup() is a member of the class task1
{
  Task2::led_2 = 14;
  pinMode(led_2, OUTPUT);
}

void Task2::loop()
{
  Serial.print(" TASK_2... ");
  digitalWrite(led_2, HIGH);
  delay(1000);
  digitalWrite(led_2, LOW);
  delay(1000);
}
