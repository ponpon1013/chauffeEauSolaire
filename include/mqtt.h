#ifndef MQTT_LOCAL
#define MQTT_LOCAL

#include <Ticker.h>
#include <AsyncMqttClient.h>

#define MQTT_HOST IPAddress(192, 168, 0, 1)
#define MQTT_PORT 1883

#define MQTT_SUBSCRIB_CHAUFFE_EAU_CHAUFFE "chauffeEau/chauffe"
#define MQTT_SUBSCRIB_CHAUFFE_EAU_CIRCULE "chauffeEau/circule"
#define MQTT_SUBSCRIB_CHAUFFE_EAU_REMPLIS "chauffeEau/remplis"
#define MQTT_SUBSCRIB_CHAUFFE_EAU_VIDE "chauffeEau/vide"
#define MQTT_SUBSCRIB_CHAUFFE_EAU_CONSIGNE_MAX "chauffeEau/consMax"
#define MQTT_SUBSCRIB_CHAUFFE_EAU_CONSIGNE_MIN "chauffeEau/consMin"

void connectToMqtt();
void onMqttConnect(bool);
void onMqttDisconnect(AsyncMqttClientDisconnectReason);
void onMqttSubscribe(uint16_t , uint8_t );
void onMqttUnsubscribe(uint16_t);
void onMqttMessage(char* , char* , AsyncMqttClientMessageProperties , size_t , size_t , size_t );
void onMqttPublish(uint16_t );
void initMqtt();

#endif