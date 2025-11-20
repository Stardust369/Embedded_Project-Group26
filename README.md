# Smart Home Automation System

A modular Arduino-based Smart Home Automation project that demonstrates **fire/smoke detection**, **Bluetooth-controlled lighting**, and a **temperature-controlled fan**.  
This repository provides the complete setup instructions, wiring guidance, and code for all individual modules and the combined system.

---

## 📌 Features Overview

### 1. Fire & Smoke Alarm System
- Uses **DHT11** to measure temperature  
- Uses **MQ-2** gas sensor to detect smoke/LPG  
- Activates a **buzzer** when thresholds are exceeded  
- Prints real-time data to the Serial Monitor  
- Alerts whenever fire/smoke/gas hazard is detected  

### 2. Bluetooth-Controlled Lighting
- Uses **HC-05 Bluetooth module**  
- Allows light/LED to be turned ON/OFF from any Android phone  
- Communication handled through SoftwareSerial  
- Uses simple Bluetooth terminal/mobile app commands  

### 3. Temperature-Controlled Fan
- Uses **DHT11** to measure ambient temperature  
- Uses **L298N motor driver** and a DC fan  
- Fan speed adjusts automatically:
  - Below 29°C → Low  
  - 29–32°C → Medium  
  - Above 32°C → High  
- 16×2 LCD (I2C) displays current temperature and fan speed status  

---

## 🛠 Hardware Requirements

### Common Components
- Arduino Uno  
- Breadboard  
- Jumper Wires  
- External 9V–12V motor power supply  

### Fire/Smoke Alarm Components
- DHT11 Temperature & Humidity Sensor  
- MQ-2 Gas/Smoke Sensor  
- Buzzer  
- Resistors (optional pull-up)

### Bluetooth-Controlled Light Components
- HC-05 Bluetooth Module  
- LED + current-limiting resistor  

### Temperature-Controlled Fan Components
- DHT11  
- L298N Motor Driver  
- DC Fan Motor  
- 16×2 LCD with I2C Backpack  
- External power supply for motor  

---

## 📡 Wiring Overview

### Fire/Smoke Alarm
- DHT11:
  - VCC → 5V
  - GND → GND
  - DATA → D2

- MQ-2:
  - VCC → 5V
  - GND → GND
  - AOUT → A0

- Buzzer:
  - VCC → D8
  - GND → GND


### Bluetooth-Controlled Lighting
- HC-05:
  - VCC → 5V
  - GND → GND
  - TX → Arduino RX (through voltage divider 1kΩ–2kΩ)
  - RX → Arduino TX

- LED:
  - Anode → D10 (via 220Ω resistor)
  - Cathode → GND


### Temperature-Controlled Fan
- DHT11:
  - DATA → D7

- L298N:
  - ENA → D9 (PWM)
  - IN1 → D10
  - IN2 → D11
  - Motor Power (9–12V external) → L298N VIN
  - Arduino GND ↔ L298N GND ↔ Motor supply GND (common ground!)

- LCD (I2C):
  - SDA → A4
  - SCL → A5
  - VCC → 5V
  - GND → GND


---

## 📲 Setup Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/Stardust369/Embedded_Project-Group26.git
cd Embedded_Project-Group26
```

### 2. Install Required Libraries
In Arduino IDE → **Sketch** → **Include Library** → **Manage Libraries**  
Install the following:

- **DHT Sensor Library** (by Adafruit)  
- **Adafruit Unified Sensor**  
- **LiquidCrystal_I2C**  


---

### Running Each Feature

#### Fire/Smoke Alarm
1. Upload `fire_alarm.ino`  
2. Open Serial Monitor at **9600 baud**  
3. Observe real-time temperature & smoke readings  
4. Light a match or blow light smoke near MQ-2 to test  
5. Buzzer triggers automatically when threshold is crossed  

#### Bluetooth-Controlled Lighting
1. Upload `bluetooth_lighting.ino`  
2. Pair your phone with HC-05  
   - Default password: **1234** or **0000**  
3. Open any Bluetooth terminal app (e.g., “Serial Bluetooth Terminal”)  
4. Send commands:  
   - `ON`  → LED turns **on**  
   - `OFF` → LED turns **off**  

#### Temperature-Controlled Fan
1. Upload `fan_system.ino`  
2. Connect external **9–12V** supply to L298N  
3. 16×2 LCD displays current temperature and fan status  
4. Fan speed adjusts automatically:  
   - **Low**     → Below 29°C  
   - **Medium**  → 29–32°C  
   - **High**    → Above 32°C  

---

### Integration Notes
- Carefully check **pin conflicts** when combining all modules  
- **All grounds must be common** (Arduino GND ↔ L298N GND ↔ Power supply GND)  
- **Never** power the DC fan directly from Arduino 5V — always use external supply  
- Modules are independent and can run simultaneously once wired correctly  

---

### Project Domain & Objective
**Domain:** Embedded Systems & IoT Smart Home Automation  
**Objective:** Build a multi-feature smart system capable of:  
- Detecting fire/smoke hazards  
- Remote lighting control via Bluetooth  
- Automatic indoor temperature-based cooling  

**Enjoy building your Smart Home!**  
