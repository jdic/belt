#include <Arduino.h>
#include "Config.h"
#include "Servomotor/Servomotor.h"
#include "DispenserUnit/DispenserUnit.h"

Servomotor servomotor(Config::Pins::SORTER_SERVO);
DispenserUnit dispenser(Config::Pins::STEPPER_STEP, Config::Pins::STEPPER_DIR, 33);

void setup()
{
  servomotor.init();
  dispenser.init();
}

void loop()
{
  servomotor.update();
  dispenser.update();
}
