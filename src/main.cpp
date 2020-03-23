#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

void setup() {
  //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    wifiManager.autoConnect("ChauffeEauConnectAP");
}

void loop() {
  // put your main code here, to run repeatedly:
}