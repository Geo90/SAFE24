#include "test_schedule.h"

int led_1 = 14;
int led_2 = 12;

void setup() {
  Serial.begin(115200);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  myNewTask(&task_led1);
  myNewTask(&task_led2);
}

void task_led1() {
  digitalWrite(led_1, HIGH);
  delay(3);
  digitalWrite(led_1, LOW);
}

void task_led2() {
  digitalWrite(led_2, HIGH);
  delay(0.5);
  digitalWrite(led_2, LOW);
}

void loop() {
    
}
