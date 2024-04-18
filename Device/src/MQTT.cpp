#include "MQTT.h"

#include <WiFi.h>
#include <mqtt_client.h>
#include "secrets.h"
#include "config.h"

static esp_mqtt_client_handle_t s_Client;

void MQTT::Connect()
{
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi connection failed!");
    }
    else
    {
        Serial.print("WiFi connected. IP-Adress: ");
        Serial.println(WiFi.localIP());
    }

    esp_mqtt_client_config_t config = esp_mqtt_client_config_t();
    config.host = MQTT_HOSTNAME;
    config.port = MQTT_PORT;

    s_Client = esp_mqtt_client_init(&config);
    if (s_Client == NULL)
    {
        Serial.println("MQTT Client Init Error");
    }
    if (esp_mqtt_client_start(s_Client) != ESP_OK)
    {
        Serial.println("MQTT Client Start Error");
    }

    Serial.println("MQTT Client Connected!");
}

void MQTT::Publish(const std::string& topic, const std::string& data, int32_t qos, bool retain)
{
    int32_t error = esp_mqtt_client_publish(s_Client, topic.c_str(), data.c_str(), 0, qos, retain ? 1 : 0);

    if (error == -1)
    {
        Serial.println("MQTT::Publish(): Something went wrong.");
    }   
}