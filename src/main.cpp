#include <Arduino.h>
#include "Config.h"
#include "ServoDriver.h"

ServoDriver sortingServo(Config::Pins::SORTER_SERVO);

void setup()
{
  sortingServo.init();
  sortingServo.setAngle(45);
}

void loop()
{
  sortingServo.update();
}
