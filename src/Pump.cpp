#include <Arduino.h>
#include "Pump.h"

#define PUMP_PIN 12

void Pump::Init()
{
    pinMode(PUMP_PIN, OUTPUT);
}

void Pump::ActivateForDuration(uint32_t durationInMillis)
{
    digitalWrite(PUMP_PIN, HIGH);
    delay(durationInMillis);
    digitalWrite(PUMP_PIN, LOW);
}