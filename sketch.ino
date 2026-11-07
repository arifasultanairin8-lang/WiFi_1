#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* serverName = "http://httpbin.org/get?sensor=";

const int sensorPin = 4; // GPIO 4
const int ledPin = 2;    // GPIO 2 for Status LED

unsigned long lastTime = 0;
unsigned long timerDelay = 3000; // Every 3 seconds

void setup() {
  Serial.begin(115200);

  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);

  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      
      String serverPath = String(serverName) + String(sensorValue);
      http.begin(serverPath.c_str());
      
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);

        // Turn ON LED using ESP32 W1TS register (GPIO 2)
        REG_WRITE(GPIO_OUT_W1TS_REG, (1 << ledPin));
        delay(200); 
        // Turn OFF LED using W1TC register
        REG_WRITE(GPIO_OUT_W1TC_REG, (1 << ledPin));
        
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }

  delay(100); 
}

