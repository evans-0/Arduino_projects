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

String index_html(float temp, float humid){
  String str = "<!DOCTYPE HTML>";
  str += "<html>";
  str += "<title>Temperature</title>";
  str += "<meta http-equiv=\"refresh\" content=\"2\", name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  str += "<body><center><h1><b>Temperature:  </b>";
  str += (float)temp;
  str += " C<br><b>Humidity: </b>";
  str += humid;
  str += " %</h1></center></body></html>";
  return str;
}

float readTemp(){
  return dht.readTemperature();
}

float readHumidity(){
  return dht.readHumidity();
}

void setup(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);
  Serial.begin(9600);
  dht.begin();
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html(readTemp(),readHumidity()).c_str());
  });
  
  server.begin();
}

void loop(){
}