#include <OTAsetup.h>
#include <ESP8266WebServer.h>
#include <myServerCommands.h>

void setup() {
  OTAsetup();
  pinMode(LED_BUILTIN,OUTPUT); 

  myServerCommands::setupPageResources();
  myServerCommands::setupRouting();
  serverHTTP.begin(); 
  lighteffects::setupFastleds();
  
}

void loop() {
  serverHTTP.handleClient();
  ArduinoOTA.handle();
}
