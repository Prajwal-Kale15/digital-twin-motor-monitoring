#  A real-time Digital Twin system for motor health monitoring using ESP32, featuring predictive maintenance, fault detection, and live dashboard visualization.

## Overview

This project is a **real-time motor health monitoring system** using ESP32.
It collects data from sensors and displays it on a live dashboard for predictive maintenance.

---

## Key Innovation
- Low-cost digital twin implementation
- Real-time health scoring system
- Automatic fault detection + motor cutoff
- Scalable for industrial use

---

## Features

* Real-time monitoring (Temperature, Current, Vibration)
* Health score calculation (0–100)
* Fault detection system
* Auto cutoff for unsafe conditions
* Live dashboard using Streamlit
* Digital Twin concept implementation

---

## Working

1. ESP32 collects sensor data
2. Data is processed and health score is calculated
3. Data is sent via Serial
4. Python reads data
5. Streamlit dashboard visualizes system health

---

## Fault Conditions

* Temperature > 27°C → Warning (Yellow LED)
* Temperature > 36°C → Critical (Red LED + Buzzer + Motor OFF)
* High current → Motor cutoff
* High vibration → Health decreases

---

## Technologies Used

* ESP32
* Arduino IDE
* Python (PySerial)
* Streamlit

---

## Project Structure

* `reader.py` → Reads serial data
* `app.py` → Dashboard UI

---

##  How to Run

1. Upload Arduino code to ESP32
2. Run:

   ```bash
   python reader.py
   ```
3. In new terminal:

   ```bash
   streamlit run app.py
   ```

---

##  Outcome

* Real-time motor monitoring achieved
* Fault detection implemented
* Digital Twin dashboard created

---

## Hardware Connections

### Temperature Sensor (LM35)

* VCC → 5V (ESP32)
* GND → GND
* OUT → GPIO 34

---

### Current Sensor (ACS712)

* VCC → 5V
* GND → GND
* OUT → GPIO 35

---

### Vibration Sensor (Analog)

* VCC → 3.3V
* GND → GND
* OUT → GPIO 32

---

### LEDs

* Green LED → GPIO 25 (Normal)
* Yellow LED → GPIO 26 (Warning)
* Red LED → GPIO 27 (Fault)

---

### Buzzer

* Positive → GPIO 14
* Negative → GND

---

### Motor (via Relay Module)

* Relay IN → GPIO 33
* VCC → 5V
* GND → GND
* Motor connected through relay switch

---

### Switch (Manual Control)

* One side → GPIO 4
* Other side → GND
* Use INPUT_PULLUP in code

---


## 👨‍💻 Author

Prajwal Kale
