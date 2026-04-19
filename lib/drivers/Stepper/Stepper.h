#ifndef STEPPER_DRIVER_H
#define STEPPER_DRIVER_H

#include <Arduino.h>
#include "Config.h"

class Stepper
{
  private:
    uint8_t stepPin;
    uint8_t dirPin;

    long currentPosition;
    long targetPosition;

    unsigned long stepInterval;
    unsigned long lastStepTime;

  public:
    Stepper(uint8_t stepPin, uint8_t dirPin);

    void init();

    void move(long steps);
    void moveTo(long position);
    void stop();

    void setSpeed(unsigned long interval);
    void setspeedRPM(int rpm, int stepsPerRev = Config::Pins::STEPPER_STEPS_PER_REV);

    void update();

    bool isMoving();
    long getPosition();
    long getDistanceToGo();
};

#endif
