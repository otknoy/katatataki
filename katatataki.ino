#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "wifi_config.h"

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);

  // WiFi.config(IPAddress(192,168,1,60),IPAddress(192,168,1,1),IPAddress(255,255,255,0));
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
  server.handleClient();
}
