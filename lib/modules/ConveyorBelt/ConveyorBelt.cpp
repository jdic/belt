#include "ConveyorBelt.h"

ConveyorBelt* ConveyorBelt::instance = nullptr;

void ConveyorBelt::isrWrapperA()
{
  if (instance != nullptr)
  {
    instance->handleEncoderA();
  }
}

void ConveyorBelt::handleEncoderA()
{
  if (digitalRead(encoderPinB) == LOW)
  {
    encoderTicks++;
  }

  else
  {
    encoderTicks--;
  }
}

ConveyorBelt::ConveyorBelt(uint8_t pwmPin, uint8_t encoderPinA, uint8_t encoderPinB, float ppr)
  : motor(pwmPin)
{
  this->encoderPinA = encoderPinA;
  this->encoderPinB = encoderPinB;
  this->pulsesPerRevolution = ppr;

  this->encoderTicks = 0;
  this->currentRPM = 0.0;
  this->targetRPM = 0.0;
  this->currentPWMPercent = 0.0;

  this->kp = 1.0;
  this->ki = 0.0;
  this->kd = 0.0;
  this->integralError = 0.0;
  this->lastError = 0.0;

  this->lastUpdateTime = 0;
  this->updateInterval = 50; // 50ms (20Hz)
  this->isRunning = false;

  instance = this;
}

void ConveyorBelt::init()
{
  motor.init();
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrWrapperA, RISING);
}

void ConveyorBelt::start(float rpm)
{
  targetRPM = rpm;
  isRunning = true;
  integralError = 0.0;
  lastError = 0.0;
}

void ConveyorBelt::pause()
{
  isRunning = false;
  motor.stop();
}

void ConveyorBelt::resume()
{
  isRunning = true;
}

void ConveyorBelt::stopEmergency()
{
  isRunning = false;
  targetRPM = 0.0;
  motor.stop();
  integralError = 0.0;
}

void ConveyorBelt::tunePID(float p, float i, float d)
{
  kp = p;
  ki = i;
  kd = d;
  integralError = 0.0;
}

void ConveyorBelt::update()
{
  unsigned long currentMillis =  millis();
  unsigned long dt = currentMillis - lastUpdateTime;

  if (dt >= updateInterval)
  {
    lastUpdateTime = currentMillis;

    // Eliminar interrupciones, evitar que pulsos erroneos corrompan la lectura
    noInterrupts();
    long currentTicks = encoderTicks;
    encoderTicks = 0;
    interrupts();

    // RPM = (ticks / pulsos_por_rev) * (60000 ms / dt)
    currentRPM = ((float)currentTicks / pulsesPerRevolution) * (60000.0 / (float)dt);

    if (isRunning && targetRPM > 0)
    {
      float error = targetRPM - currentRPM;

      float pTerm = kp * error;

      integralError += (error * (dt / 1000.0));
      if (integralError > 100.0) integralError = 100.0;
      if (integralError < -100.0) integralError = -100.0;
      float iTerm = ki * integralError;

      float derivative = (error - lastError) / (dt / 1000.0);
      float dTerm = kd * derivative;

      currentPWMPercent = (pTerm + iTerm + dTerm);

      if (currentPWMPercent > 100.0) currentPWMPercent = 100.0;
      if (currentPWMPercent < .0) currentPWMPercent = 0.0;

      motor.setSpeedPercent(currentPWMPercent);

      lastError = error;
    }
  }
}

float ConveyorBelt::getRPM()
{
  return currentRPM;
}

float ConveyorBelt::getTargetRPM()
{
  return targetRPM;
}

float ConveyorBelt::getPWMPercent()
{
  return currentPWMPercent;
}

long ConveyorBelt::getEncoderTicks()
{
  noInterrupts();
  long ticks = instance->encoderTicks;
  interrupts();
  return ticks;
}
