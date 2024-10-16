#pragma once

#include <WebServer.h>

class Router {
public:
  Router(WebServer& server);
  void handleClient();

private:
  WebServer& server;
  void handleRoot();
  void handleApi();
};

