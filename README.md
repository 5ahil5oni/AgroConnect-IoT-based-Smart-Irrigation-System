AgroConnect: IoT-Based Soil Irrigation System

This project is an IoT-based smart irrigation system using ESP8266, DHT11, Ultrasonic Sensor, and Blynk App. It also has it's custom website to aid users.

Features

- Real-time temperature, humidity, and soil moisture monitoring.
- Ultrasonic sensor for flood/water level detection.
- Automatic display updates on LCD.
- Notifications and monitoring through the Blynk App.
- Activates a buzzer or pump when water tank is full or soil is dry.

Components Used

| Component                    | Quantity   |
|------------------------------|------------|
| NodeMCU ESP8266              | 1          |
| DHT11 Sensor                 | 1          |
| Ultrasonic Sensor (HC-SR04)  | 1          |
| Soil Moisture Sensor         | 1          |
| I2C LCD (16x2)               | 1          |
| Connecting wires, breadboard | As needed  |

Circuit Overview

- DHT11 connected to D4
- Ultrasonic Trigger = D1, Echo = D2
- Soil Sensor = A0
- LCD uses I2C protocol (address `0x27`)
- Buzzer connected to D0

 Blynk Virtual Pins

| Data             | Virtual Pin |
|------------------|-------------|
| Temperature      | V1          |
| Humidity         | V2          |
| Water Level      | V0          |
| Soil Moisture    | V3          |

How It Works

- Ultrasonic sensor detects water level, classified into `Very Low`, `Low`, `Medium`, `High`, and `Full`.
- DHT11 tracks temperature and humidity.
- Soil Sensor reports dryness — triggers alert if very dry.
- All data is displayed on LCD and sent to the Blynk app for remote monitoring.

Getting Started

1. Open `main.ino` in Arduino IDE.
2. Install required libraries:
   - `Blynk`
   - `ESP8266WiFi`
   - `DHT`
   - `LiquidCrystal_I2C`
3. Enter your:
   ```cpp
   #define BLYNK_AUTH_TOKEN "your_blynk_token"
   char ssid[] = "your_wifi_ssid";
   char pass[] = "your_wifi_password";
4. Upload to NodeMCU.
5. Monitor via Serial Monitor or Blynk App.


# AgroConnect-IoT-based-Smart-Irrigation-System
