#ifndef GEAR_MOTOR_H
#define GEAR_MOTOR_H

#include <Arduino.h>

class Gearmotor
{
  private:
    uint8_t pwmPin;
    int currentSpeed;
  
  public:
    Gearmotor(uint8_t pwmPin);

    void init();

    void setSpeed(int speed);
    void setSpeedPercent(float percent);
    void stop();

    int getSpeed();
    bool isRunning();
};

#endif
