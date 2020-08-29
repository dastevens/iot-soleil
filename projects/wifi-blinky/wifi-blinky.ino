#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "secrets.h"
const char *ssid     = SECRET_SSID;
const char *password = SECRET_PASSWORD;

ESP8266WebServer server(80);

void handle() {
  server.send(200, "text/html",
  "<html>"
  "<head>"
  "<style>"
  "body {"
  "  padding: 2em;"
  "  background-color: black;"
  "  text-align: center;"
  "}"
  "button {"
  "  background-color: #4CAF50;"
  "  border: none;"
  "  color: white;"
  "  padding: 4em;"
  "  font-size: 2em;"
  "  margin: 4px 2px;"
  "  border-radius: 30%;"
  "}"
  "</style>"
  "</head>"
  "<body>"
  "  <button onClick='fetch(\"/toggle\")'>Toggle</button>"
  "</body>"
  "</html>"
  );
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  delay(3000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handle);
  server.begin();
  Serial.println("HTTP server started");
  server.on("/toggle", []() {
    if (digitalRead(LED_BUILTIN)) {
      Serial.println("0");
      digitalWrite(LED_BUILTIN, 0);
      handle();
    } else {
      Serial.println("1");
      digitalWrite(LED_BUILTIN, 1);
      handle();
    }
  });
}
void loop() {
  server.handleClient();
}
