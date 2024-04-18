#pragma once

#include <mqtt_client.h>

class MQTT
{
public:
    static void Connect();

    static esp_mqtt_client_handle_t s_Client;
};