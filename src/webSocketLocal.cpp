#include "webScoketLocal.h"

WebSocketsServer webSocket = WebSocketsServer(81);

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

void initWebSocket(){
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loopWebSocket(){
    webSocket.loop();
}