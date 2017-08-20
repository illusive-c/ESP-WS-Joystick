#include <ESP8266WiFi.h>
#include "FS.h"
#include <WiFiClient.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include "FSWebServerLib.h"
#include <Hash.h>

static void writeLED(bool);

int x,y;

AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws

// Rutine for repeat part of the code every X miliseconds
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))
                         
void setup() {
  // WiFi is started inside library
  SPIFFS.begin(); // Not really needed, checked inside library and started if needed
  ESPHTTPServer.begin(&SPIFFS);
  /* add setup code here */
  
  // attach AsyncWebSocket
  ws.onEvent(onEvent);
  ESPHTTPServer.addHandler(&ws);
}

void loop() {
  // DO NOT REMOVE. Attend OTA update from Arduino IDE
  ESPHTTPServer.handle();
  //WS Ping Routine
  runEvery(100) {
    ws.textAll("ping");
    }
}
