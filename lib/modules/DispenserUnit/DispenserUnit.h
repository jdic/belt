#ifndef DIEPNSER_UNIT_H
#define DIEPNSER_UNIT_H

#include <Arduino.h>
#include "Stepper/Stepper.h"
#include "Config.h"

class DispenserUnit
{
  private:
    Stepper stepper;
    long stepsPerToken;

  public:
    DispenserUnit(uint8_t stepPin, uint8_t dirPin, long stepsPerToken = Config::Values::DISPENSER_STEPS_PER_TOKEN);

    void init();

    void dispenseToken();
    void stopEmergency();
    
    void update();

    bool isReady();
};

#endif
