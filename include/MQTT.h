#pragma once

#include <string>

class MQTT
{
public:
    static void Connect();

    static void Publish(const std::string& topic, const std::string& data, int32_t qos, bool retain);
    static void Publish(const std::string& topic, int32_t            data, int32_t qos, bool retain);

};