#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <Arduino.h>
#include <Servo.h>

class ServoDriver
{
  private:
    Servo servo;
    uint8_t pin;
    int currentAngle;
    int targetAngle;
    unsigned long lastUpdateTime;
    unsigned long updateInterval;

  public:
    ServoDriver(uint8_t pin);

    void init();

    void setAngle(int angle);
    void setSpeed(unsigned long interval);

    void update();
    int getCurrentAngle();
};

#endif
