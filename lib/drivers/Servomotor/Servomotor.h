#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include <Arduino.h>
#include <Servo.h>

class Servomotor
{
  private:
    Servo servo;
    uint8_t pin;
    int currentAngle;
    int targetAngle;
    unsigned long lastUpdateTime;
    unsigned long updateInterval;

  public:
    Servomotor(uint8_t pin);

    void init();

    void setAngle(int angle);
    void forceAngle(int angle);
    void setSpeed(unsigned long interval);

    void update();
    
    int getCurrentAngle();
    int getTargetAngle();
    bool isMoving();
    bool isAttached();
};

#endif
