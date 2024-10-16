#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "router.h"

int pinADC = 33;

const float R2 = 5000;  // en ohmios
const float R1 = 2000; 

const float V_REF = 3.3; 
const float MAX_VOLTAGE = 4.0; // voltaje maximo de la bateria




Router::Router(WebServer& server) : server(server) {
  server.on("/", [this]() {handleRoot();});
  server.on("/getData", [this]() {handleApi();});
}

void Router::handleClient() {
  server.handleClient();
}

void Router::handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "Not found");
    return;
  }
  String html = file.readString();
  server.send(200, "text/html", html);
  file.close();
}

void Router::handleApi() {
    StaticJsonDocument<200> res;

    int valorADC = analogRead(pinADC);
    float voltaje = ((float)valorADC / 4095.0) * V_REF;
    voltaje = voltaje * (R1 + R2) / R2;
    float percentage = (voltaje / MAX_VOLTAGE) * 100;
    if (percentage > 100) percentage = 100;
    const char* status = (voltaje < MAX_VOLTAGE * 0.2) ? "descargando" : "cargando";

    res["volts"] = voltaje;
    res["percentage"] = percentage;
    res["status"] = status;

    String plain;
    serializeJson(res, plain);

    server.send(200, "application/json", plain);
}
