#include <Arduino.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include "router.h"



#ifdef DEBUG
  #define DbgPrint(x) Serial.println(x)
  constexpr const char *SSID = "";
  constexpr const char *PASSWORD = "";
#else 
  #define DbgPrint(x)
  constexpr const char *SSID = "ENERGON";
  constexpr const char *PASSWORD = "energon999555";
#endif


WebServer server(80);
Router router(server);


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  if(!SPIFFS.begin(true)) {
    DbgPrint("error iniciando spiffs");
    return;
  }

#ifdef DEBUG
  DbgPrint("debugging mode :fire:");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    DbgPrint("conectando...");
    delay(1000);
  }
  DbgPrint("conectado");
  DbgPrint(WiFi.localIP());
#else 
  WiFi.softAP(SSID, PASSWORD);
  Serial.println(WiFi.softAPIP());
#endif // DEBUG
  server.begin();
}

void loop() {
  router.handleClient();
}
