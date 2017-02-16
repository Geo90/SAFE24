#include "Tasks.h" 


//--------------------------------------------------
//-------------------- TaskPIR ---------------------
//--------------------------------------------------

void TaskPIR::setup() // :: => "binary scope resolution operator", setup() is a member of the class task1
{
 
  Serial.begin(115200);
  
  // Variables
  TaskPIR::sensorPin = A0;
  TaskPIR::ledPin1 = 14;
  TaskPIR::ledPin2 = 12;
  TaskPIR::pir = 13;
  TaskPIR::prevTime = 0;
  TaskPIR::sensorValue = 0;
  TaskPIR::pirCounter = 0;
  TaskPIR::pirSum = 0;
  
  // PinModes
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
  pinMode(pir, INPUT);
  pinMode(sensorPin, INPUT);
  prevTime = 0;
  

}

void TaskPIR::loop()
{
  Serial.print(" TaskPIR... ");
  
}

void TaskPIR::doWithPirValue(int pirvalue)
{
  if (pirvalue == HIGH){
    pirCounter = pirCounter + 1;
    pirSum = pirSum + 10;
  }

  if (pirvalue == LOW){
    pirCounter = pirCounter + 1;
  }
}

void TaskPIR::doWhenMove() {
  if (pirCounter == 7) {
    pirCounter = 0;
    if (pirSum == 70) {
      prevTime = millis();
      digitalWrite(ledPin1, HIGH);
    }
    if (pirSum < 70 && ( millis()  - prevTime ) > 10000 ) {
      digitalWrite(ledPin1, LOW);
      prevTime = 0;
    }
    pirSum = 0;
  }  
}

//--------------------------------------------------
//-------------------- TaskPIR ---------------------
//--------------------------------------------------



