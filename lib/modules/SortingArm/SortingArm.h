#ifndef SORTING_ARM_H
#define SORTING_ARM_H

#include <Arduino.h>
#include "Servomotor/Servomotor.h"
#include "OpticalSensor/OpticalSensor.h"

enum TokenColor
{
  COLOR_UNKNOWN,
  COLOR_WHITE,
  COLOR_BLACK
};

class SortingArm
{
  private:
    Servomotor servo;
    OpticalSensor sensor;

    int neutralAngle;
    int whiteAngle;
    int blackAngle;

    TokenColor lastDetectedColor;

  public:
    SortingArm(uint8_t servoPin, uint8_t sensorPin, bool sensorActiveHigh = true);

    void init();

    TokenColor evaluateColor();
    void sort(TokenColor color);
    void evaluateAndSort();
    void resetPosition();

    void update();

    bool isReady();

    TokenColor getLastColor();
    int getSensorRawValue();
    void setSensorThreshold(int threshold);
};

#endif
