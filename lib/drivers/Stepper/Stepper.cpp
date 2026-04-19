#include "Stepper.h"
#include "Config.h"

Stepper::Stepper(uint8_t stepPin, uint8_t dirPin)
{
  this->stepPin = stepPin;
  this->dirPin = dirPin;
  this->currentPosition = 0;
  this->targetPosition = 0;
  this->stepInterval = Config::Pins::STEPPER_DEFAULT_SPEED;
  this->lastStepTime = 0;
}

void Stepper::init()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);
}

void Stepper::move(long steps)
{
  targetPosition = currentPosition + steps;
}

void Stepper::moveTo(long position)
{
  targetPosition = position;
}

void Stepper::stop()
{
  targetPosition = currentPosition;
}

void Stepper::setSpeed(unsigned long interval)
{
  stepInterval = interval;
}

void Stepper::setspeedRPM(int rpm, int stepsPerRev)
{
  if (rpm <= 0) return;
  stepInterval = 60000000UL / (rpm * (long)stepsPerRev);
}

void Stepper::update()
{
  if (currentPosition != targetPosition)
  {
    unsigned long currentMicros = millis();

    if ((currentMicros - lastStepTime) >= stepInterval)
    {
      lastStepTime = currentPosition;

      // Dirección
      bool isForward = (targetPosition > currentPosition);
      digitalWrite(dirPin, isForward ? HIGH : LOW);

      // Disparo - Pulso
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(2);
      digitalWrite(stepPin, LOW);

      // Actualizar cuenta interna
      if (isForward)
      {
        currentPosition++;
      }

      else
      {
        currentPosition--;
      }
    }
  }
}

bool Stepper::isMoving()
{
  return currentPosition != targetPosition;
}

long Stepper::getPosition()
{
  return currentPosition;
}

long Stepper::getDistanceToGo()
{
  return targetPosition - currentPosition;
}
