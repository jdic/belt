#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

namespace Config
{
  namespace Pins
  {
    // Motoreductor
    const uint8_t GEARMOTOR_ENCODER_A = 2;
    const uint8_t GEARMOTOR_ENCODER_B = 3;
    const uint8_t GEARMOTOR_PWM = 5;

    // Motor a pasos
    const uint8_t STEPPER_STEP = 4;
    const uint8_t STEPPER_DIR = 7;

    // Clasificador
    const uint8_t SORTER_SERVO = 9;

    // Sensores
    const uint8_t COLOR_SENSOR = 8;
  }

  namespace Values
  {
    
    const uint8_t STEPPER_STEPS_PER_REV = 200;
    const unsigned long STEPPER_DEFAULT_SPEED = 2000UL;
    const uint8_t DISPENSER_STEPS_PER_TOKEN = 33;
  }

  namespace System
  {
    const unsigned long SERIAL_BAUD_RATE = 115200UL;
  }
}

#endif
