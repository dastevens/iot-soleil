#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <DHT.h>

#include "secrets.h"
const char *ssid     = SECRET_SSID;
const char *password = SECRET_PASSWORD;

#define DHT11_PIN 2
DHT dht(DHT11_PIN, DHT11);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  delay(1000);
}

void postDataPoint(char* name, float value) {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(SECRET_ADDRESS);
    
    // Specify content-type header
    http.addHeader("Content-Type", "multipart/mixed");
    // Data to send with HTTP POST
    String httpRequestData = String(name) + String(",device=") + String(SECRET_DEVICE_NAME) + String(" value=") + String(value);
    // Send HTTP POST request
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
      
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}


void loop() {
  const float temperature = dht.readTemperature();
  Serial.print("T = ");
  Serial.println(temperature);
  postDataPoint("temperature", temperature);

  const float humidity = dht.readHumidity();
  Serial.print("H = ");
  Serial.println(humidity);
  postDataPoint("humidity", humidity);
  delay(60000);
}