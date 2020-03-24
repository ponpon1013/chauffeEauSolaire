#ifndef HANDLER
#define HANDLER

#include <ESP8266WebServer.h>

#define SCRIPTS_PATH "/scripts/"
#define CSS_PATH "/css/"

class MyHandlerJavascript : public RequestHandler {

  public:
  
    bool canHandle(HTTPMethod , String );
    bool handle(ESP8266WebServer& , HTTPMethod , String );
};

class MyHandlerCSS : public RequestHandler {

    public:
        bool canHandle(HTTPMethod , String ) ;
        bool handle(ESP8266WebServer& , HTTPMethod , String ) ;
};

#endif