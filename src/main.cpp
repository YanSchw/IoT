#include <Arduino.h>

#include "MQTT.h"
#include "BMP.h"

void setup()
{
    Serial.begin(9600);
    MQTT::Connect();
    BMP::Init();

    // Send Status Online
    MQTT::Publish("devices/project/status", "online", 2, true);
}

void loop()
{
    MQTT::Publish("devices/project/temp", BMP::GetTemperature(), 2, false);
    MQTT::Publish("devices/project/pressure", BMP::GetPressure(), 2, false);
    MQTT::Publish("devices/project/altitude", BMP::GetAltitude(), 2, false);
    delay(5000);
}
