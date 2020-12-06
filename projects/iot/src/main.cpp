#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <wifi.h>

#include <DHT.h>

#include "secrets.h"

#define DHT11_PIN 2
DHT dht(DHT11_PIN, DHT11);

void setup() {
  Serial.begin(9600);
  configureWifi();
  dht.begin();
  delay(1000);
}

void postDataPoint(const char* name, float value) {
  HTTPClient http;
  http.begin(String(SECRET_ADDRESS));
  http.addHeader("Content-Type", "multipart/mixed");
  String httpRequestData = String(name) + String(",device=") + String(SECRET_DEVICE_NAME) + String(" value=") + String(value);
  Serial.println(httpRequestData);
  int httpResponseCode = http.POST(httpRequestData);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
}

void loop() {
  if (enableWifi()) {
    postDataPoint("temperature", dht.readTemperature());
    postDataPoint("humidity", dht.readHumidity());
  }
  disableWifi();
  delay(300e3);
}