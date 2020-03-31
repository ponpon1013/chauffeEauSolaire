#include "handler.h"

bool MyHandlerJavascript::canHandle(HTTPMethod method, String uri) {
   return uri !=NULL && uri.startsWith(SCRIPTS_PATH) ;
 }

 bool MyHandlerJavascript::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {   
    Serial.println(requestUri);
    File dataFile = SPIFFS.open(requestUri.c_str(), "r"); 
    server.send(200,"application/javascript",dataFile.readString());
    return true;
  }

  bool MyHandlerCSS::canHandle(HTTPMethod method, String uri) {
   return uri !=NULL && uri.startsWith(CSS_PATH) ;
 }

 bool MyHandlerCSS::handle(ESP8266WebServer& server, HTTPMethod requestMethod, String requestUri) {   
    Serial.println(requestUri);
    File dataFile = SPIFFS.open(requestUri.c_str(), "r"); 
    server.send(200,"text/css",dataFile.readString());
    return true;
  }