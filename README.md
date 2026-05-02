# 🔧 Digital Twin Motor Health Monitoring System

## 📌 Overview

This project is a **real-time motor health monitoring system** using ESP32.
It collects data from sensors and displays it on a live dashboard for predictive maintenance.

---

## ⚙️ Features

* Real-time monitoring (Temperature, Current, Vibration)
* Health score calculation (0–100)
* Fault detection system
* Auto cutoff for unsafe conditions
* Live dashboard using Streamlit
* Digital Twin concept implementation

---

## 🧠 Working

1. ESP32 collects sensor data
2. Data is processed and health score is calculated
3. Data is sent via Serial
4. Python reads data
5. Streamlit dashboard visualizes system health

---

## 🚨 Fault Conditions

* Temperature > 27°C → Warning (Yellow LED)
* Temperature > 36°C → Critical (Red LED + Buzzer + Motor OFF)
* High current → Motor cutoff
* High vibration → Health decreases

---

## 📊 Technologies Used

* ESP32
* Arduino IDE
* Python (PySerial)
* Streamlit

---

## 📂 Project Structure

* `reader.py` → Reads serial data
* `app.py` → Dashboard UI

---

## 🚀 How to Run

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

## 🎯 Outcome

* Real-time motor monitoring achieved
* Fault detection implemented
* Digital Twin dashboard created

---

## 👨‍💻 Author

Prajwal Kale
