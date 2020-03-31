#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h> 
#include <ArduinoOTA.h>
#include <FS.h>
#include "handler.h"
#include "mqtt.h"
#include "webScoketLocal.h"

ESP8266WebServer server ( 80 );

MyHandlerJavascript handlerJS;
MyHandlerCSS handlerCSS;


void handleRootSpiffsError() {
  server.send(200, "text/plain", "SPIFFS KO!");
  }

void setup() {
  Serial.begin ( 9600 );
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  wifiManager.autoConnect("ChauffeEauConnectAP");

  //si on arrive là c'est qu'on est connecté au reseau

  //******* OTA ***************
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("ESPTest");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();

  //********* Fin OTA ***************
    

    if (!SPIFFS.begin())
  {
    // Serious problem
    Serial.println("SPIFFS Mount failed");
    server.on("/", handleRootSpiffsError);
    
  } else {
    Serial.println("SPIFFS Mount succesfull");
    server.addHandler(&handlerJS);
    server.addHandler(&handlerCSS );
    server.serveStatic("/", SPIFFS, "/index.html");
  }
  
  server.begin();
  Serial.println ( "HTTP server started" );
 
  initWebSocket();

  initMqtt();
  connectToMqtt();

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  loopWebSocket();
  ArduinoOTA.handle();
  delay(100);
}