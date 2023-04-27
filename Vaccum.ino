#include <Tic.h>
#include "motor.h"
#ifdef SERIAL_PORT_HARDWARE_OPEN
#define ticSerial SERIAL_PORT_HARDWARE_OPEN
#else
#include <SoftwareSerial.h>
SoftwareSerial ticSerial(10, 11);
#endif

TicSerial frontTic(ticSerial, 14);
TicSerial backTic(ticSerial, 15);

motor theMotor;

int MotorSpeed = 225;
//middle
const int IRsensorR1 = 5;
const int IRsensorL1 = 6;
//rear
const int IRsensorR2 = 2;
const int IRsensorL2 = 3;

void setup()
{
  // Set the baud rate.
  Serial.begin(9600);
  delay(20);

  frontTic.exitSafeStart();
  backTic.exitSafeStart();
  pinMode(IRsensorR1,INPUT); // IR Sensor pin INPUT
  pinMode(IRsensorL1,INPUT); // IR Sensor pin INPUT
  pinMode(IRsensorR2,INPUT); // IR Sensor pin INPUT
  pinMode(IRsensorL2,INPUT); // IR Sensor pin INPUT

}

void resetCommandTimeout()
{
  frontTic.resetCommandTimeout();
  backTic.resetCommandTimeout();

}

void delayWhileResettingCommandTimeout(uint32_t ms)
{
  uint32_t start = millis();
  do
  {
    resetCommandTimeout();
  } while ((uint32_t)(millis() - start) <= ms);
}

void waitForPosition(int32_t targetPosition)
{
  do
  {
    frontTic.resetCommandTimeout();
  } while (frontTic.getCurrentPosition() != targetPosition);
}



void loop() {
   int sensorStatusR1 = digitalRead(IRsensorR1);
   int sensorStatusL1 = digitalRead(IRsensorL1); 
   int sensorStatusR2 = digitalRead(IRsensorR2);
   int sensorStatusL2 = digitalRead(IRsensorL2); 
 

   if (Serial.available()){
  
  int move = Serial.parseInt();
  if (move == 5){
      Serial.print("forward");

    }
    
    switch(move) {
    case 5:
        Serial.println("forward");
        theMotor.speedControl(125);
        theMotor.directionControl_forward();
        break;
    case 2:
        Serial.println("backward");
        theMotor.speedControl(125);
        theMotor.directionControl_backward();
        break;
    case 1:
        if (sensorStatusR1 == 0 && sensorStatusL1 == 0) {
        theMotor.leftspeedControl(125);
        theMotor.directionControl_left();
        Serial.println("left");
        }
        else if (sensorStatusR1 == 1 || sensorStatusL1 == 1) {
        theMotor.directionControl_forward();
        theMotor.speedControl(125);
        Serial.println("forward");
        }
  
        break;

    case 3:
        if (sensorStatusR1 == 0 && sensorStatusL1 == 0){
        theMotor.rightspeedControl(125);
        theMotor.directionControl_right() ;
        Serial.println("right");
        }
        else if(sensorStatusR1 == 1 || sensorStatusL1 == 1){
        theMotor.directionControl_forward();
        theMotor.speedControl(125);
        Serial.println("forward");
        }
        break;
    case 4: 
        theMotor.speedControl(0);
          Serial.println("stopMotor");
        break;
    case 7:
        frontTic.setTargetPosition(100);
        Serial.println("frontUp");
        break;
    case 8:
        frontTic.setTargetPosition(0);
        backTic.setTargetPosition(0);
        Serial.println("centralUp");
        break;
    case 9:
        backTic.setTargetPosition(9);
        Serial.println("backUp");
        break;
        
  }
   }
  
  uint32_t frontpostion = frontTic.getCurrentPosition();
  uint32_t backpostion = backTic.getCurrentPosition();



}
