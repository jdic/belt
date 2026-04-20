#include <Arduino.h>
#include <ArduinoJson.h>
#include "Config.h"

#include "DispenserUnit/DispenserUnit.h"
#include "SortingArm/SortingArm.h"
#include "ConveyorBelt/ConveyorBelt.h"

DispenserUnit dispenser(Config::Pins::STEPPER_STEP, Config::Pins::STEPPER_DIR, 33);
SortingArm sortingArm(Config::Pins::SORTER_SERVO, Config::Pins::COLOR_SENSOR, true);
ConveyorBelt conveyor(Config::Pins::GEARMOTOR_PWM, Config::Pins::GEARMOTOR_ENCODER_A, Config::Pins::GEARMOTOR_ENCODER_B, 330.0);

enum SystemState
{
  STATE_IDLE,
  STATE_DISPENSING,
  STATE_CONVEYING,
  STATE_SORTING,
  STATE_WAIT_DROP,
  STATE_PAUSE,
  STATE_ESTOP
};

SystemState currentState = STATE_IDLE;
SystemState stateBeforePause = STATE_IDLE;

unsigned long lastTelemetryTime = 0;
const unsigned long TELEMETRY_INTERVAL = 200;
int countWhite = 0;
int countBlack = 0;

unsigned long dropTimer = 0;
const unsigned long DROP_DELAYS_MS = 1500;

void handleSerialCommands();
void sendTelemetry();
void runFSM();

void setup()
{
  Serial.begin(Config::System::SERIAL_BAUD_RATE);

  dispenser.init();
  sortingArm.init();
  conveyor.init();

  sortingArm.setSensorThreshold(500);
}

void loop()
{
  dispenser.update();
  sortingArm.update();
  conveyor.update();

  handleSerialCommands();
  runFSM();
  sendTelemetry();
}

void runFSM()
{
  switch (currentState)
  {
    case STATE_IDLE:
      break;

    case STATE_DISPENSING:
      if (dispenser.isReady())
      {
        dispenser.dispenseToken();
        currentState = STATE_CONVEYING; 
      }

      break;

    case STATE_CONVEYING:
      if (dispenser.isReady())
      {
        conveyor.start(60.0);

        if (sortingArm.evaluateColor() != COLOR_UNKNOWN)
        {
          conveyor.pause();
          currentState = STATE_SORTING;
        }
      }

      break;

    case STATE_SORTING:
      sortingArm.evaluateAndSort();

      if (sortingArm.isReady())
      {
        if (sortingArm.getLastColor() == COLOR_WHITE) countWhite++;
        if (sortingArm.getLastColor() == COLOR_BLACK) countBlack++;

        dropTimer = millis();
        currentState = STATE_WAIT_DROP;
      }

      break;

    case STATE_WAIT_DROP:
      if (millis() - dropTimer >= DROP_DELAYS_MS)
      {
        sortingArm.resetPosition();
        currentState = STATE_DISPENSING;
      }

      break;

    case STATE_PAUSE:
      break;

    case STATE_ESTOP:
      conveyor.stopEmergency();
      dispenser.stopEmergency();
      sortingArm.resetPosition();
      break;
  }
}

void handleSerialCommands()
{
  if (Serial.available() > 0)
  {
    JsonDocument document;
    DeserializationError error = deserializeJson(document, Serial);

    if (!error)
    {
      String command = document["cmd"];

      if (command == "SET_STATE")
      {
        String value = document["val"];

        if (value == "START")
        {
          currentState = STATE_DISPENSING;
        }

        else if (value == "PAUSE")
        {
          stateBeforePause = currentState;
          conveyor.pause();
          currentState = STATE_PAUSE;
        }

        else if (value == "RESUME")
        {
          conveyor.resume();
          currentState = stateBeforePause;
        }

        else if (value == "ESTOP")
        {
          currentState = STATE_ESTOP;
        }
      }

      else if (command == "TUNE_PID")
      {
        float kp = document["kp"];
        float ki = document["ki"];
        float kd = document["kd"];

        conveyor.tunePID(kp, ki, kd); 
      }

      else if (command == "SET_THRESHOLD")
      {
        int threshold = document["val"];

        sortingArm.setSensorThreshold(threshold);
      }
    }
  }
}

void sendTelemetry()
{
  unsigned long currentMillis = millis();

  if (currentMillis - lastTelemetryTime >= TELEMETRY_INTERVAL)
  {
    lastTelemetryTime = currentMillis;

    JsonDocument document;

    String stateStr = "IDLE";
    if (currentState == STATE_CONVEYING) stateStr = "CONVEYING";
    else if (currentState == STATE_SORTING) stateStr = "SORTING";
    else if (currentState == STATE_ESTOP) stateStr = "ESTOP";

    document["sys_state"] = stateStr;
    document["belt_rpm"] = conveyor.getRPM();
    document["belt_pwm"] = conveyor.getPWMPercent();
    document["sensor_raw"] = sortingArm.getSensorRawValue();
    document["count_w"] = countWhite;
    document["count_b"] = countBlack;

    serializeJson(document, Serial);
    Serial.println();
  }
}
