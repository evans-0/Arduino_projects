# html_temp

An ESP32-based web server that reads temperature and humidity from a DHT22 sensor and serves the data as a live webpage over a local WiFi access point.

## What it does

The ESP32 creates its own WiFi hotspot. Any device connected to it can open a browser and view the current temperature (°C) and humidity (%) — the page auto-refreshes every 2 seconds.

## Hardware

| Component | Details |
|-----------|---------|
| Microcontroller | ESP32 |
| Sensor | DHT22 (temperature + humidity) |
| Data pin | GPIO 4 |

## Wiring

```
DHT22 VCC  →  3.3V
DHT22 GND  →  GND
DHT22 DATA →  GPIO 4
```

> Add a 10kΩ pull-up resistor between the DATA and VCC pins if readings are unstable.

## Dependencies

Install via Arduino Library Manager:

- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) — Adafruit
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) *(required by ESPAsyncWebServer)*

Board support: **ESP32** via Arduino IDE Boards Manager.

## Configuration

Edit these lines in `html_temp.ino` before uploading:

```cpp
const char* ssid     = "quark";       // Hotspot name
const char* password = "012345678";   // Hotspot password (min 8 chars)
```

## Usage

1. Upload the sketch to your ESP32.
2. Open the Serial Monitor at **9600 baud** — the AP IP address will be printed (default: `192.168.4.1`).
3. Connect your phone or laptop to the `quark` WiFi network.
4. Navigate to `http://192.168.4.1` in a browser.

## Known limitations

- The HTML page is rebuilt as a `String` on every request — fine for low traffic, but inefficient at scale.
- No error handling if the DHT22 returns `NaN` (sensor not connected or read failure).
- Credentials are hardcoded in plain text.
