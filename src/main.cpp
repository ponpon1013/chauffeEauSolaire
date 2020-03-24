#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h> 
#include <WebSocketsServer.h>
#include <FS.h>
#include "handler.h"

ESP8266WebServer server ( 80 );
WebSocketsServer webSocket = WebSocketsServer(81);
MyHandlerJavascript handlerJS;
MyHandlerCSS handlerCSS;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    String toPrint;
    switch(type) {
        case WStype_DISCONNECTED:
            toPrint=String(num)+ " Disconnected";
            Serial.println(toPrint);
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                toPrint=String(num)+ " Connected from "+ip[0]+"."+ ip[1]+"."+ ip[2]+"."+ ip[3];
                Serial.println(toPrint);
				
				// send message to client
				webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
            //Serial.println(num+" get Text:"+ payload);

            // send message to client
            // webSocket.sendTXT(num, "message here");

            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            /*Serial.println(num+" get binary length:"+length);
            hexdump(payload, length);*/

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    }

}



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
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  webSocket.loop();
  delay(100);
}