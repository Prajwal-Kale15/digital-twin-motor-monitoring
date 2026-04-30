import streamlit as st
import serial
import time

st.set_page_config(page_title="Digital Twin", layout="wide")

st.markdown("<h1 style='text-align:center;'>⚙️ Smart Monitoring Dashboard</h1>", unsafe_allow_html=True)

# SERIAL CONNECTION
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    st.success("✅ ESP32 Connected")
except:
    st.error("❌ Close Arduino / reader.py")
    st.stop()

time.sleep(2)

# ----------- FIXED PLACEHOLDERS (KEY PART) -----------

st.markdown("### 📊 System Metrics")

col1, col2, col3 = st.columns(3)
temp_box = col1.empty()
current_box = col2.empty()
vib_box = col3.empty()

col4, col5, col6 = st.columns(3)
health_box = col4.empty()
rul_box = col5.empty()
risk_box = col6.empty()

st.markdown("### 🚨 Alerts")
alert_box = st.empty()

st.markdown("### 📈 Live Trends")
chart_box = st.empty()

# DATA STORAGE
temp_list = []
current_list = []
health_list = []

# ----------- MAIN LOOP -----------

while True:
    try:
        line = ser.readline().decode(errors='ignore').strip()

        if "Temp:" not in line:
            continue

        parts = line.split(" | ")

        temp = float(parts[0].split(": ")[1])
        current = float(parts[1].split(": ")[1])
        vib = float(parts[2].split(": ")[1])
        health = int(parts[3].split(": ")[1])
        fault = int(parts[4].split(": ")[1])

        # Derived
        rul = (health / 100) * 100
        risk = 100 - health

        # ----------- UPDATE METRICS (NO NEW ELEMENTS) -----------

        temp_box.metric("🌡️ Temperature", f"{temp:.2f} °C")
        current_box.metric("⚡ Current", f"{current:.2f} A")
        vib_box.metric("📳 Vibration", f"{vib:.1f} %")

        health_box.metric("❤️ Health", f"{health}%")
        rul_box.metric("⏳ RUL", f"{rul:.1f} hrs")
        risk_box.metric("⚠️ Risk", f"{risk}%")

        # ----------- ALERTS (REPLACED EACH TIME) -----------

        with alert_box.container():
            if temp > 36:
                st.error("🔴 CRITICAL: Temperature too high! Motor stopped.")
            elif temp > 27:
                st.warning("🟡 WARNING: Temperature rising.")
            elif fault == 1:
                st.error("🚨 SYSTEM FAULT!")
            else:
                st.success("✅ System Normal")

        # ----------- GRAPH (UPDATED, NOT STACKED) -----------

        temp_list.append(temp)
        current_list.append(current)
        health_list.append(health)

        if len(temp_list) > 50:
            temp_list.pop(0)
            current_list.pop(0)
            health_list.pop(0)

        chart_box.line_chart({
            "Temp": temp_list,
            "Current": current_list,
            "Health": health_list
        })

        time.sleep(1)

    except:
        time.sleep(1)