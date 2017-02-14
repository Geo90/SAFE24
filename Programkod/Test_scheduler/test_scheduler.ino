#include "test_schedule.h"

//--------------------------------------------------
//----- TASK 1 -----
//--------------------------------------------------
class BlinkLed_1 : public Task {
  public:
  
  const int led_1 = 12;
    
    void setup() 
    {
      pinMode(led_1, OUTPUT);
    }
    
    void loop() 
    {
      Serial.print(" LED_1 TASK ");
      digitalWrite(led_1, HIGH);
      delay(5000);
      digitalWrite(led_1, LOW);
      delay(5000);
    }
    
} led1_task;


//--------------------------------------------------
//----- TASK 2 -----
//--------------------------------------------------
class BlinkLed_2 : public Task {
  public:
  
  const int led_2 = 14;
    
    void setup() 
    {
      pinMode(led_2, OUTPUT);
    }
    
    void loop() 
    {
      Serial.print(" LED_2 TASK ");
      digitalWrite(led_2, HIGH);
      delay(1000);
      digitalWrite(led_2, LOW);
      delay(1000);
    }
    
} led2_task;


//--------------------------------------------------
//----- SETUP -----
//--------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.print("ESP8266 SETUP");
  myNewTask(&led1_task);
  myNewTask(&led2_task);
  startTasks();
}

void loop() {
    // ...
}
