#pragma once

#include <string>

// Helper Class for dealing with the BMP280 Sensor
class BMP
{
public:
    static void Init();

    static uint32_t GetTemperature();
};