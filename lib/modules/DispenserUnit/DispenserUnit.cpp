#include "DispenserUnit.h"
#include "Config.h"

DispenserUnit::DispenserUnit(uint8_t stepPin, uint8_t dirPin, long stepsPerToken)
  : stepper(stepPin, dirPin)
{
  this->stepsPerToken = stepsPerToken;
}

void DispenserUnit::init()
{
  stepper.init();
  stepper.setSpeed(Config::Values::STEPPER_DEFAULT_SPEED);
}

void DispenserUnit::dispenseToken()
{
  if (stepper.isMoving())
  {
    stepper.move(stepsPerToken);
  }
}

void DispenserUnit::stopEmergency()
{
  stepper.stop();
}

void DispenserUnit::update()
{
  stepper.update();
}

bool DispenserUnit::isReady()
{
  return !stepper.isMoving();
}
