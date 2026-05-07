#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "quark";
const char* password = "012345678";

const char* tempServer = "http://192.168.4.1/temp";

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String temperature;
unsigned long previousMillis = 0;
const long interval = 5000;

void setup() {
  Serial.begin(9600);
  Serial.println();

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  oled.clearDisplay();
  oled.setTextColor(WHITE);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval){
    if (WiFi.status() == WL_CONNECTED){
      temperature = httpGETRequest(tempServer);
      Serial.println("Temperature: " + temperature + " C");
      
      oled.clearDisplay();
      oled.setTextSize(2);
      oled.setCursor(0,0);
      oled.print(temperature);
      oled.print(" ");
      oled.setTextSize(1);
      oled.cp437(true);
      oled.write(248);
      oled.setTextSize(2);
      oled.print("C");
      oled.display();

      previousMillis = currentMillis;
    }
    else{
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}