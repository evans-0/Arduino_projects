#include "DHT.h"
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#define DHTPIN 4
#define DHTTYPE DHT22

const char* ssid = "quark";
const char* password = "012345678";

DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTemp(){
  return String(dht.readTemperature());
}

void setup(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  Serial.begin(9600);
  dht.begin();
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/temp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());});
  
  server.begin();
}

void loop(){
}