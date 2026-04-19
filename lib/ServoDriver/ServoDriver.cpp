#include "ServoDriver.h"

ServoDriver::ServoDriver(uint8_t pin)
{
  this->pin = pin;
  this->currentAngle = 90;
  this->targetAngle = 90;
  this->lastUpdateTime = 0;
  this->updateInterval = 15;
}

void ServoDriver::init()
{
  servo.attach(pin);
  servo.write(currentAngle);
};

void ServoDriver::setAngle(int angle)
{
  // Restricción de seguridad
  targetAngle = constrain(angle, 0, 180);
};

void ServoDriver::setSpeed(unsigned long interval)
{
  updateInterval = interval;
};

void ServoDriver::update()
{
  if (currentAngle != targetAngle)
  {
    unsigned long currentMillis = millis();

    if ((currentMillis - lastUpdateTime) >= updateInterval)
    {
      lastUpdateTime = currentMillis;

      if (currentAngle < targetAngle)
      {
        currentAngle++;
      }

      else
      {
        currentAngle--;
      }

      servo.write(currentAngle);
    }
  }
}

int ServoDriver::getCurrentAngle()
{
  return currentAngle;
}
