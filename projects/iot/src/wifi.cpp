#include <Arduino.h>
#include <ESP8266WiFi.h>

#define CONNECTION_TIMEOUT_MS 10000
#define CONNECTION_CHECK_MS 200

#include "secrets.h"
const char *ssid     = SECRET_SSID;
const char *password = SECRET_PASSWORD;

void configureWifi() {
  Serial.println("Configuring Wifi...");
  WiFi.persistent(false);
  delay(1);
  Serial.println("Configured Wifi");
}

bool enableWifi() {
  Serial.println("Enabling Wifi...");

  // Power up WiFi
  WiFi.forceSleepWake();

  // Use Station mode (wifi client)
  WiFi.mode(WIFI_STA);
  delay(1);

  // Connect
  WiFi.begin(SECRET_SSID, SECRET_PASSWORD);

  for (int timeout = CONNECTION_TIMEOUT_MS; timeout >= 0; timeout -= CONNECTION_CHECK_MS) {
    delay(CONNECTION_CHECK_MS);
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("Wifi enabled");
      return true;
    }
    Serial.print(".");
  }

  Serial.println("Failed to enable Wifi");
  return false;
}

void disableWifi() {
  Serial.println("Disabling Wifi...");

  WiFi.disconnect(true);
  delay(1);
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.println("Disabled Wifi");
}
