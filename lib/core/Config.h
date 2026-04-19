#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

namespace Config
{
  namespace Pins
  {
    // Banda Transporadora
    const uint8_t CONVEYOR_ENCODER_A = 2;
    const uint8_t CONVEYOR_ENCODER_B = 3;
    const uint8_t CONVEYOR_PWM = 5;

    // Dipensador
    const uint8_t DISPENSER_STEP = 4;
    const uint8_t DISPENSER_DIR = 7;

    // Clasificador
    const uint8_t SORTER_SERVO = 9;

    // Sensores
    const uint8_t COLOR_SENSOR = 8;
  }

  namespace System
  {
    const unsigned long SERIAL_BAUD_RATE = 115200;
  }
}

#endif
