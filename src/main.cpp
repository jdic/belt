#include <Arduino.h>
#include "Config.h"
#include "Servomotor/Servomotor.h"

Servomotor servomotor(Config::Pins::SORTER_SERVO);

void setup()
{
  servomotor.init();
  servomotor.setAngle(45);
}

void loop()
{
  servomotor.update();
}
