#include "Gearmotor.h"

Gearmotor::Gearmotor(uint8_t pwmPin)
{
  this->pwmPin = pwmPin;
  this->currentSpeed = 0;
}

void Gearmotor::init()
{
  pinMode(pwmPin, OUTPUT);
  stop();
}

void Gearmotor::setSpeed(int speed)
{
  currentSpeed = constrain(speed, 0, 255);
  analogWrite(pwmPin, currentSpeed);
}

void Gearmotor::setSpeedPercent(float percent)
{
  float constrainedPercent = constrain(percent, 0.0, 100.0);
  int pwmValue = map(constrainedPercent, 0, 100, 0, 255);
  setSpeed(pwmValue);
}

void Gearmotor::stop()
{
  analogWrite(pwmPin, 0);
}

int Gearmotor::getSpeed()
{
  return currentSpeed;
}

bool Gearmotor::isRunning()
{
  return currentSpeed > 0;
}
