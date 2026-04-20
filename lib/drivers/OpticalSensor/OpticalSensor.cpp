#include "OpticalSensor.h"

OpticalSensor::OpticalSensor(uint8_t analogPin, bool activeHigh)
{
  this->analogPin = analogPin;
  this->activeHigh = activeHigh;
  this->threshold = 512;
}

void OpticalSensor::init()
{
  pinMode(analogPin, INPUT);
}

void OpticalSensor::setThreshold(int thresholdValue)
{
  this->threshold = constrain(thresholdValue, 0, 1023);
}

int OpticalSensor::getRawValue()
{
  return analogRead(analogPin);
}

bool OpticalSensor::isWhite()
{
  int raw = getRawValue();

  if (activeHigh)
  {
    return raw > threshold;
  }

  else
  {
    return raw < threshold;
  }
}

bool OpticalSensor::isBlack()
{
  int raw = getRawValue();

  if (activeHigh)
  {
    return raw <= threshold;
  }

  else
  {
    return raw >= threshold;
  }
}
