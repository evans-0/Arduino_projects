# temp_sensor

A wireless temperature monitoring system using two ESP boards. The **transmitter** reads temperature from a DHT22 sensor and hosts it over a local Wi-Fi access point. The **receiver** connects to that access point, fetches the temperature every 5 seconds, and displays it on an OLED screen.

## Project Structure

```
temp_sensor/
├── transmitter/
│   └── transmitter.ino   # ESP32 — DHT22 sensor + WiFi AP + HTTP server
└── receiver/
    └── receiver.ino      # ESP8266 — fetches temp + displays on OLED
```

## Hardware Requirements

### Transmitter
- ESP32 board
- DHT22 temperature & humidity sensor
- 10kΩ pull-up resistor (between DATA and VCC)

### Receiver
- ESP8266 board (e.g., NodeMCU, Wemos D1 Mini)
- SSD1306 OLED display (128×64, I2C)

## Pin Configuration

### Transmitter (ESP32)
| Component | Pin |
|-----------|-----|
| DHT22 DATA | GPIO 4 |

### Receiver (ESP8266)
| Component | Pins |
|-----------|------|
| SSD1306 OLED | SDA / SCL (I2C default pins) |

## Dependencies

### Transmitter
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) — Adafruit
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- `WiFi.h` (built-in with ESP32 Arduino core)

### Receiver
- [ESP8266WiFi](https://github.com/esp8266/Arduino) (built-in with ESP8266 Arduino core)
- [ESP8266HTTPClient](https://github.com/esp8266/Arduino) (built-in)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

## How It Works

1. The **transmitter** starts a WiFi access point named `quark` and runs an HTTP server on port 80.
2. A GET request to `http://192.168.4.1/temp` returns the current temperature in °C as plain text.
3. The **receiver** connects to the `quark` access point and polls `/temp` every **5 seconds**.
4. The fetched temperature is printed to the Serial monitor and rendered on the OLED display.

## Network Configuration

| Setting | Value |
|---------|-------|
| SSID | `quark` |
| Password | `012345678` |
| Transmitter IP | `192.168.4.1` (default AP IP) |
| Endpoint | `http://192.168.4.1/temp` |

## Setup & Usage

1. **Transmitter**
   - Wire the DHT22 to GPIO 4 on the ESP32.
   - Open `transmitter.ino` in Arduino IDE with the ESP32 board package installed.
   - Install the required libraries via the Library Manager.
   - Upload to the ESP32.

2. **Receiver**
   - Wire the SSD1306 OLED to the I2C pins on the ESP8266.
   - Open `receiver.ino` in Arduino IDE with the ESP8266 board package installed.
   - Install the required libraries via the Library Manager.
   - Upload to the ESP8266.

3. Power both boards. The receiver will connect to the transmitter's access point and start displaying the temperature.

## Notes

- Only temperature is read from the DHT22. Humidity data is available via `dht.readHumidity()` if needed.
- The OLED I2C address is set to `0x3C`. If your display doesn't initialize, try `0x3D`.
- To change the polling interval, modify the `interval` constant (in milliseconds) in `receiver.ino`.
- Ensure both boards are powered before checking the Serial monitor for connection logs.
