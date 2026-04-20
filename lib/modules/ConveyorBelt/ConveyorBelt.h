#ifndef CONVEYOR_BELT_H
#define CONVEYOR_BELT_H

#include <Arduino.h>
#include "Gearmotor/Gearmotor.h"

class ConveyorBelt
{
  private:
    Gearmotor motor;
    uint8_t encoderPinA;
    uint8_t encoderPinB;

    static ConveyorBelt* instance;
    static void isrWrapperA();
    void handleEncoderA();

    volatile long encoderTicks;

    float pulsesPerRevolution;
    float currentRPM;
    float targetRPM;

    float kp, ki, kd;
    float integralError;
    float lastError;
    float currentPWMPercent;

    unsigned long lastUpdateTime;
    unsigned long updateInterval;
    bool isRunning;

  public:
    ConveyorBelt(uint8_t pwmPin, uint8_t encoderPinA, uint8_t encoderPinB, float ppr = 330.0);

    void init();

    void start(float rpm);
    void pause();
    void resume();
    void stopEmergency();

    void tunePID(float p, float i, float d);

    void update();

    float getRPM();
    float getTargetRPM();
    float getPWMPercent();
    long getEncoderTicks();
};

#endif
