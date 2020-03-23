#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h> 
#include <FS.h>

#define SCRIPTS_PATH "/scripts/"
#define CSS_PATH "/css/"

ESP8266WebServer server ( 80 );

class MyHandlerJavascript : public RequestHandler {
 bool canHandle(HTTPMethod method, String uri) {
   return uri !=NULL && uri.startsWith(SCRIPTS_PATH) ;
 }

  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {   
    Serial.println(requestUri);
    File dataFile = SPIFFS.open(requestUri.c_str(), "r"); 
    server.send(200,"application/javascript",dataFile.readString());
    return true;
  }
} MyHandlerJavascript;

class MyHandlerCSS : public RequestHandler {
 bool canHandle(HTTPMethod method, String uri) {
   return uri !=NULL && uri.startsWith(CSS_PATH) ;
 }

  bool handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {   
    Serial.println(requestUri);
    File dataFile = SPIFFS.open(requestUri.c_str(), "r"); 
    server.send(200,"text/css",dataFile.readString());
    return true;
  }
} MyHandlerCSS;

void handleRootSpiffsError() {
  server.send(200, "text/plain", "SPIFFS KO!");
  }

void setup() {
  Serial.begin ( 9600 );
  //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    wifiManager.autoConnect("ChauffeEauConnectAP");

    if (!SPIFFS.begin())
  {
    // Serious problem
    Serial.println("SPIFFS Mount failed");
    server.on("/", handleRootSpiffsError);
    
  } else {
    Serial.println("SPIFFS Mount succesfull");
    server.addHandler(&MyHandlerJavascript);
    server.addHandler(&MyHandlerCSS);
    server.serveStatic("/", SPIFFS, "/index.html");
  }
  
  server.begin();
  Serial.println ( "HTTP server started" );
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  delay(100);
}