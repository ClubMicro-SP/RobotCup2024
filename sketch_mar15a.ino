#include "Grove_I2C_Motor_Driver.h"

#define I2C_ADDRESS 0x0f


int echo = 0;
int echodroit = 0;
int echogauche = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}


void setup()
{
  Motor.begin(I2C_ADDRESS);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
}

void loop()

{
  echo = 0.01723 * readUltrasonicDistance(6, 5);
  echodroit = 0.01723 * readUltrasonicDistance(4, 3);
  echogauche = 0.01723 * readUltrasonicDistance(2, 1);

  if (echo <= 10 ) {
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    Motor.speed(MOTOR1,-100);
    Motor.speed(MOTOR2, -100);
    delay(300);
    Motor.stop(MOTOR1);
    Motor.stop(MOTOR2);
    delay(2000);
    if (echogauche < 20) {
      Motor.speed(MOTOR1,-100);
      Motor.speed(MOTOR2, 100);
    }else{
      Motor.stop(MOTOR1);
      Motor.stop(MOTOR2);
      Motor.speed(MOTOR1,100);
      Motor.speed(MOTOR2, 100);
      delay(300);
      Motor.stop(MOTOR1);
      Motor.stop(MOTOR2);
      delay(1000);
    }
      
  } else {
        Motor.speed(MOTOR1,-100);
        Motor.speed(MOTOR2, 100);
  }

}
