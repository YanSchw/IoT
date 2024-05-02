#include "MQTT.h"

#include <WiFi.h>
#include <mqtt_client.h>
#include "secrets.h"
#include "config.h"

#include "Pump.h"

static esp_mqtt_client_handle_t s_Client;

static esp_err_t mqtt_event_callback(esp_mqtt_event_handle_t event)
{
    if (event->event_id == MQTT_EVENT_DATA)
    {
        Serial.println("MQTT Event: DATA Received");
        Serial.print("Topic: ");
        std::string topic = std::string(event->topic, event->topic_len);
        Serial.println(topic.c_str());

        Serial.print("Message: "); 
        std::string message = std::string(event->data, event->data_len);
        Serial.println(message.c_str());

        if (topic == "event/pump")
        {
            const uint32_t duration = std::abs(std::atoi(message.c_str()));
            Pump::ActivateForDuration(duration ? duration : 1000);
        }
    }

    return {};
}

void MQTT::Connect()
{
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

    // Setup Last Will & Testament
    config.lwt_retain = 1;
    config.lwt_msg = "offline";
    config.lwt_qos = 2;
    config.lwt_topic = "devices/project/status";
    config.keepalive = 10;
    //config.disable_auto_reconnect = 1;

    // Setip Event Callback
    config.event_handle = &mqtt_event_callback;

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

    // Subscribe to all 'event/#'
    esp_mqtt_client_subscribe(s_Client, "event/#", 2);
}

void MQTT::Publish(const std::string& topic, const std::string& data, int32_t qos, bool retain)
{
    if (esp_mqtt_client_publish(s_Client, topic.c_str(), data.c_str(), 0, qos, retain ? 1 : 0) == -1)
    {
        Serial.println("MQTT::Publish(): Something went wrong.");
    }   
}
void MQTT::Publish(const std::string& topic, int32_t data, int32_t qos, bool retain)
{
    Publish(topic, std::to_string(data), qos, retain);
}