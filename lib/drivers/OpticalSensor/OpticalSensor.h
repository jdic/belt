#ifndef OPTICAL_SENSOR_H
#define OPTICAL_SENSOR_H

#include <Arduino.h>

class OpticalSensor
{
  private:
    uint8_t analogPin;
    int threshold;
    bool activeHigh;

  public:
    OpticalSensor(uint8_t analogPin, bool activeHigh = true);

    void init();

    void setThreshold(int thresholdValue);

    int getRawValue();

    bool isWhite();
    bool isBlack();
};

#endif
