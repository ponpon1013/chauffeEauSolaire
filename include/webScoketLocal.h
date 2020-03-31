#ifndef WEBSOCKET_LOCAL
#define WEBSOCKET_LOCAL


#include <WebSocketsServer.h>

void webSocketEvent(uint8_t , WStype_t , uint8_t * , size_t );
void initWebSocket();
void loopWebSocket();


#endif