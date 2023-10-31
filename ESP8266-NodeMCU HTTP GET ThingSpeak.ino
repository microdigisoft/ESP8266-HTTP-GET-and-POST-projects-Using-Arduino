#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* thingspeakApiKey = "your_thingspeak_api_key";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    const int sensorValue = analogRead(A0); // Read your sensor value here
    String data = "field1=" + String(sensorValue); // Modify the field number based on your ThingSpeak channel configuration
    
    if (client.connect("api.thingspeak.com", 80)) {
      client.print("GET /update?");
      client.print(data);
      client.print("&api_key=");
      client.print(thingspeakApiKey);
      client.println(" HTTP/1.1");
      client.println("Host: api.thingspeak.com");
      client.println("Connection: close");
      client.println();
      delay(500); // Delay for stability
      client.stop();
      
      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.println("Error connecting to ThingSpeak");
    }
  }
  
  delay(60000); // Delay for 1 minute before updating again
}