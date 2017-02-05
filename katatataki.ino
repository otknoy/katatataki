#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>


#include "wifi_config.h"

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);

  WiFi.config(IPAddress(192, 168, 0, 5),
	      IPAddress(192, 168, 0, 1),
	      IPAddress(255, 255, 255, 0));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();


  server.on("/", []() {
      String s = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"></head><body>";
      s = s + "<p>ssid: " + ssid + "</p>";
      s = s + "<p>: " + ssid + "</p>";
      s = s + "<p>IP address: " + WiFi.localIP() + "</p>";
      s = s + "</body></html>";

      server.send(200, "text/html", s);
    });

  server.on("/shoulder/tap", handleTapShoulder);
  server.on("/shoulder/right/blink", handleRightShoulderLed);
  server.on("/shoulder/left/blink", handleLeftShoulderLed);

  server.onNotFound([]() {
      String message = "File Not Found\n\n";
      message += "URI: ";
      message += server.uri();
      message += "\nMethod: ";
      message += (server.method() == HTTP_GET) ? "GET" : "POST";
      message += "\nArguments: ";
      message += server.args();
      message += "\n";
      for (uint8_t i = 0; i < server.args(); i++) {
	message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      }

      server.send(404, "text/plain", "message");
    });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  ArduinoOTA.handle();

  server.handleClient();

  yield();
}
