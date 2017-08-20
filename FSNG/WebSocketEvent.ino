
void parseString(uint8_t *data){
  String temp = (char*)data;
  if (temp.substring(0, 1) = "XY") {
    String xt = (temp.substring(3));
    String x = (xt.substring(0,xt.indexOf(',')));
    String y = (xt.substring(xt.indexOf(',')+1));
    Serial.print("X: "+ x );
    Serial.println(", Y: "+ y );
  }
  }

void onEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    //client connected
    os_printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  }
  else if (type == WS_EVT_DISCONNECT) {
    //client disconnected
    os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  }
  else if (type == WS_EVT_ERROR) {
    //error was received from the other end
    os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  }
  else if (type == WS_EVT_PONG) {
    //pong message was received (in response to a ping request maybe)
    os_printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char*)data : "");
  }
  else if (type == WS_EVT_DATA) {
    //data packet
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len) {
      //the whole message is in a single frame and we got all of it's data
      os_printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);
      if (info->opcode == WS_TEXT) {
        data[len] = 0;
        //os_printf("%s DATA \n", (char*)data);
        parseString(data);
        
      } else {
        for (size_t i = 0; i < info->len; i++) {
          os_printf("%02x ", data[i]);
        }
        os_printf("\n");
      }
//      if (info->opcode == WS_TEXT)
//        client->text("I got your text message");
//      else
//        client->binary("I got your binary message");
    } 
  }
}
