#include <Arduino.h>

#include "MQTT.h"

void setup()
{
    Serial.begin(9600);
    MQTT::Connect();
}

void loop()
{
    MQTT::Publish("devices/project/test", rand() % 10, 2, false);
    delay(5000);
}
