# 🌱 CropGuard-AI

> Arduino + Edge Impulse ML system for real-time tomato crop health monitoring — built by **Ajadi Ayomide (Danlos)**

![Arduino](https://img.shields.io/badge/Arduino-Nano%2033%20BLE-00979D?style=flat&logo=arduino)
![Edge Impulse](https://img.shields.io/badge/Edge%20Impulse-ML%20Model-purple)
![Accuracy](https://img.shields.io/badge/Model%20Accuracy-100%25-brightgreen)
![Wokwi](https://img.shields.io/badge/Simulated-Wokwi-orange)
![License](https://img.shields.io/badge/License-MIT-blue)

---

## 📌 Overview

CropGuard-AI is an embedded machine learning project that monitors tomato crop health using environmental sensors and an on-device ML model trained with Edge Impulse. It classifies crop conditions in real time into three categories and triggers visual and audio alerts accordingly — all running directly on an Arduino microcontroller with no internet connection required.

---

## 🎯 Classification Labels

| Label | Meaning | Sensor Pattern | Indicator |
|-------|---------|----------------|-----------|
| 🟢 `safe` | Crop is healthy | Low soil moisture, low temp, high humidity, high light | Green LED ON |
| 🟡 `stressed` | Crop needs attention | Mid soil moisture, mid temp, moderate humidity | Yellow LED ON |
| 🔴 `critical` | Crop is in danger | High soil moisture, high temp, low humidity, low light | Red LED + Buzzer |

---

## 🔧 Hardware Components

| Component | Pin | Purpose |
|-----------|-----|---------|
| Arduino Nano 33 BLE | — | Main microcontroller |
| DHT22 | D2 | Temperature + Humidity |
| Soil Moisture Sensor | A0 | Soil moisture readings |
| LDR | A1 | Light intensity |
| Green LED | D5 | Safe status indicator |
| Yellow LED | D6 | Stressed status indicator |
| Red LED | D7 | Critical status indicator |
| Buzzer | D8 | Audio alert for critical state |

---

## 🧠 ML Model (Edge Impulse)

- **Platform:** Edge Impulse Studio
- **Input features:** `soil_moisture`, `temperature`, `humidity`, `light`
- **Classes:** `critical`, `safe`, `stressed`
- **Dataset:** 48 samples (critical: 17, safe: 15, stressed: 16)
- **Architecture:** Neural Network — Dense(20) → Dense(10) → Output(3)
- **Accuracy:** **100%** on validation set
- **F1 Score:** 1.00 for all 3 classes
- **RAM usage:** 16 bytes (ultra-lightweight)
- **Target board:** Arduino Nano 33 BLE (Cortex-M4F 80MHz)

---

## 🖥️ Demo

### Wokwi Simulation
The project runs fully in [Wokwi](https://wokwi.com) — no physical hardware needed.

**Circuit running — Yellow LED (stressed) active:**

```
Sensors → Arduino Nano 33 BLE → Edge Impulse Model → LED/Buzzer Output
   |              |                      |                    |
 DHT22          D2 pin            100% accuracy          Green/Yellow/Red
 Soil → A0      A0/A1             real-time inference    + Buzzer on critical
 LDR  → A1
```

### Serial Monitor Output (sample)
```
CropGuard-AI Starting...
Soil: 45.00 | Temp: 32.50 | Humidity: 52.00 | Light: 620.00
Prediction: stressed (98.7%)
---
Soil: 20.00 | Temp: 27.00 | Humidity: 76.00 | Light: 850.00
Prediction: safe (99.2%)
---
Soil: 81.00 | Temp: 38.40 | Humidity: 28.00 | Light: 418.00
Prediction: critical (97.5%)
---
```

---

## 📁 Project Structure

```
CropGuard-AI/
├── sketch/
│   ├── sketch.ino              # Main Arduino code
│   ├── sketch.ino.bin          # Compiled binary
│   ├── sketch.ino.elf          # ELF file for Wokwi
│   ├── sketch.ino.hex          # Hex file
│   └── sketch.ino.map          # Memory map
├── diagram.json                # Wokwi circuit diagram
├── wokwi.toml                  # Wokwi simulator config
└── README.md
```

---

## 🚀 How to Run

### Option 1 — Wokwi Simulation (VS Code)
1. Clone this repo
2. Open in VS Code
3. Install [Wokwi VS Code extension](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode)
4. Press `F1` → **Wokwi: Start Simulator**
5. Watch the LEDs respond to sensor values!

### Option 2 — Real Hardware
1. Flash `sketch/sketch.ino.bin` to Arduino Nano 33 BLE
2. Connect sensors as per pin table above
3. Open Serial Monitor at **115200 baud**
4. Observe real-time crop health predictions

### Option 3 — Recompile from Source
```powershell
# Install Edge Impulse library
arduino-cli lib install --zip-path ei-cropguard-ai-arduino-1.0.1.zip

# Compile
arduino-cli compile --fqbn arduino:mbed_nano:nano33ble --output-dir sketch sketch/
```

---

## 🌍 Real-World Application

This project is designed with **Nigerian smallholder farmers** in mind. Tomatoes are one of Nigeria's most important crops, and early detection of crop stress or critical conditions can prevent significant yield loss. CropGuard-AI provides:

- **No internet required** — runs fully on-device
- **Low cost** — uses affordable sensors
- **Instant alerts** — LED + buzzer for immediate farmer response
- **Expandable** — can be retrained for cassava, maize, rice and more

---

## 👨🏾‍💻 Author

**Ajadi Ayomide (Danlos)**
- GitHub: [@ayomideajadi12-hub](https://github.com/ayomideajadi12-hub)
- Projects: SickleGuard-AI | CropGuard-AI

---

## 📄 License

MIT License — feel free to fork, modify and build on this project!
