#include "SortingArm.h"

SortingArm::SortingArm(uint8_t servoPin, uint8_t sensorPin, bool sensorActiveHigh)
  : servo(servoPin), sensor(sensorPin, sensorActiveHigh)
{
  this->neutralAngle = 90;
  this->whiteAngle = 45;
  this->blackAngle = 135;

  this->lastDetectedColor = COLOR_UNKNOWN;
}

void SortingArm::init()
{
  servo.init();
  sensor.init();

  servo.forceAngle(neutralAngle);
}

TokenColor SortingArm::evaluateColor()
{
  if (sensor.isWhite())
  {
    lastDetectedColor = COLOR_WHITE;
  }

  else if (sensor.isBlack())
  {
    lastDetectedColor = COLOR_BLACK;
  }

  else
  {
    lastDetectedColor = COLOR_UNKNOWN;
  }

  return lastDetectedColor;
}

void SortingArm::sort(TokenColor color)
{
  if (color == COLOR_WHITE)
  {
    servo.setAngle(whiteAngle);
  }

  else if (color == COLOR_BLACK)
  {
    servo.setAngle(blackAngle);
  }

  else
  {
    servo.setAngle(neutralAngle);
  }
}

void SortingArm::evaluateAndSort()
{
  TokenColor detectedColor = evaluateColor();
  sort(detectedColor);
}

void SortingArm::resetPosition()
{
  servo.setAngle(neutralAngle);
}

void SortingArm::update()
{
  servo.update();
}

bool SortingArm::isReady()
{
  return !servo.isMoving();
}

TokenColor SortingArm::getLastColor()
{
  return lastDetectedColor;
}

int SortingArm::getSensorRawValue()
{
  return sensor.getRawValue();
}

void SortingArm::setSensorThreshold(int threshold)
{
  sensor.setThreshold(threshold);
}
