#include "mqtt.h"
#include <ESP8266WiFi.h>

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  mqttClient.subscribe(MQTT_SUBSCRIB_CHAUFFE_EAU_CHAUFFE, 2);
  mqttClient.subscribe(MQTT_SUBSCRIB_CHAUFFE_EAU_CIRCULE, 2);
  mqttClient.subscribe(MQTT_SUBSCRIB_CHAUFFE_EAU_VIDE, 2);
  mqttClient.subscribe(MQTT_SUBSCRIB_CHAUFFE_EAU_REMPLIS, 2);
  mqttClient.subscribe(MQTT_SUBSCRIB_CHAUFFE_EAU_CONSIGNE_MAX, 2);
  mqttClient.subscribe(MQTT_SUBSCRIB_CHAUFFE_EAU_CONSIGNE_MIN, 2);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  /*Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  qos: ");
  Serial.println(properties.qos);
  Serial.print("  dup: ");
  Serial.println(properties.dup);
  Serial.print("  retain: ");
  Serial.println(properties.retain);
  Serial.print("  len: ");
  Serial.println(len);
  Serial.print("  index: ");
  Serial.println(index);
  Serial.print("  total: ");
  Serial.println(total);
  Serial.print("  payload: ");
  Serial.println(payload);*/

  // parse topics
  if (strcmp(topic,MQTT_SUBSCRIB_CHAUFFE_EAU_CONSIGNE_MAX)==0){}
  if (strcmp(topic,MQTT_SUBSCRIB_CHAUFFE_EAU_CONSIGNE_MIN)==0){}
  if (strcmp(topic,MQTT_SUBSCRIB_CHAUFFE_EAU_CHAUFFE)==0){}
  if (strcmp(topic,MQTT_SUBSCRIB_CHAUFFE_EAU_CIRCULE)==0){}
  if (strcmp(topic,MQTT_SUBSCRIB_CHAUFFE_EAU_REMPLIS)==0){}
  if (strcmp(topic,MQTT_SUBSCRIB_CHAUFFE_EAU_VIDE)==0){}
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void initMqtt(){
  Serial.println("init MQTT");
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
}
