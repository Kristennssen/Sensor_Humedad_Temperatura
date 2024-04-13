#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"// Incluye la biblioteca del sensor DHT11

#define DHTPIN 2     // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11   // Tipo de sensor DHT (DHT11 en este caso)
DHT dht(DHTPIN, DHTTYPE); // Inicializa el sensor DHT11

const char* ssid = "POCO X5 Pro 5G";
const char* password =  "abcd1234.";
const char* serverName = "http://192.168.194.83:3000/sensor2";

int cont = 300;
String ip;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

  dht.begin(); // Inicializa el sensor DHT11
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      DynamicJsonDocument doc(1024);
      doc["nombre"] = "Christian";
      doc["correo"] = "christian.aecp@gmail.com";
      doc["carne"] = "0902-21-8380";
      doc["latitud"] = "15.47083";
      doc["Longitud"] = "-90.37083";
      doc["temperatura"] = temperatura;
      doc["humedad"] = humedad;
      doc["device"] = "christian-esp32";
      doc["ip"] = "192.168.0.1";

      String jsonData;
      serializeJson(doc, jsonData);

      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(jsonData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }

    lastTime = millis();
  }
}