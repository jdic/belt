#include "Servomotor.h"

Servomotor::Servomotor(uint8_t pin)
{
  this->pin = pin;
  this->currentAngle = 90;
  this->targetAngle = 90;
  this->lastUpdateTime = 0;
  this->updateInterval = 15;
}

void Servomotor::init()
{
  servo.attach(pin);
  servo.write(currentAngle);
};

void Servomotor::setAngle(int angle)
{
  targetAngle = constrain(angle, 0, 180);
};

void Servomotor::forceAngle(int angle)
{
  int constrainedAngle = constrain(angle, 0, 180);
  currentAngle = constrainedAngle;
  targetAngle = constrainedAngle;

  if (isAttached())
  {
    servo.write(currentAngle);
  }
}

void Servomotor::setSpeed(unsigned long interval)
{
  updateInterval = interval;
}

void Servomotor::update()
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

      if (isAttached())
      {
        servo.write(currentAngle);
      }
    }
  }
}

int Servomotor::getCurrentAngle()
{
  return currentAngle;
}

int Servomotor::getTargetAngle()
{
  return targetAngle;
}

bool Servomotor::isMoving()
{
  return currentAngle != targetAngle;
}

bool Servomotor::isAttached()
{
  return servo.attached();
}
