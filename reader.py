import serial
import time

PORT = 'COM3'
BAUD = 115200

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
    print(f"✅ Connected to {PORT}")
except:
    print("❌ Close Arduino Serial Monitor or check COM port")
    exit()

time.sleep(2)

print("📡 Reading data...\n")

while True:
    try:
        line = ser.readline().decode(errors='ignore').strip()

        # Show raw line (for debugging)
        print("RAW:", line)

        if "Temp:" not in line:
            continue

        # Split safely
        parts = line.split(" | ")

        if len(parts) < 6:
            continue  # incomplete data

        temp = float(parts[0].split(": ")[1])
        current = float(parts[1].split(": ")[1])
        vib = float(parts[2].split(": ")[1])
        health = int(parts[3].split(": ")[1])
        fault = int(parts[4].split(": ")[1])
        switch = int(parts[5].split(": ")[1])

        print(f"🌡️ {temp:.2f}°C | ⚡ {current:.2f}A | 📳 {vib:.1f}% | ❤️ {health}% | 🚨 {fault} | 🔘 {switch}")

    except KeyboardInterrupt:
        print("\n🛑 Stopped by user")
        break

    except Exception as e:
        print("⚠️ Parsing error:", e)