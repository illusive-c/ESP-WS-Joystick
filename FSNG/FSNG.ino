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
#include <Wire.h>

//Gyro Test Vars
byte error, MPU_6050_found, nunchuck_found, lowByte, highByte;
int address;
int nDevices;
//end

//TEST

// defines pins numbers
const int stepPin = D6;
const int dirPin = D7;

//

static void writeLED(bool);

int x, y;

AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws

// Rutine for repeat part of the code every X miliseconds
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))


void setup() {
  // WiFi is started inside library
  SPIFFS.begin(); // Not really needed, checked inside library and started if needed
  Serial.begin(115200);
  ESPHTTPServer.begin(&SPIFFS);
  /* add setup code here */

  // attach AsyncWebSocket
  ws.onEvent(onEvent);
  ESPHTTPServer.addHandler(&ws);

  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //Gyro Test
  Wire.begin(D1, D2);
  Wire.setClock(400000L);
}

void loop() {
  // DO NOT REMOVE. Attend OTA update from Arduino IDE
  ESPHTTPServer.handle();
  //WS Ping Routine
  runEvery(1000) {
    ws.textAll("ping");
  }

  //  //Stepper Code
  //  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
  //
  //  // Makes 200 pulses for making one full cycle rotation
  //  for(int x = 0; x < 200; x++) {
  //    digitalWrite(stepPin,HIGH);
  //    delayMicroseconds(1000);
  //    digitalWrite(stepPin,LOW);
  //    delayMicroseconds(100);
  //  }
  //  delay(1000); // One second delay
  //
  //  digitalWrite(dirPin,HIGH); //Changes the rotations direction
  //  delay(5);
  //  // Makes 400 pulses for making two full cycle rotation
  //  for(int x = 0; x < 400; x++) {
  //    digitalWrite(stepPin,HIGH);
  //    delayMicroseconds(1000);
  //    digitalWrite(stepPin,LOW);
  //    delayMicroseconds(1000);
  //  }
  //  delay(1000);
}



