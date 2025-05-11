# 🌱 ESP32 Hydroponic Monitoring & Pump Control System

A smart hydroponic monitoring system using **ESP32**, capable of:
- 📏 Measuring **pH**, **EC (Electrical Conductivity)**, and **temperature**
- 🔌 Controlling **four pumps** manually via serial commands
- 🧠 Providing real-time feedback with sensor calibration support

---

## 🧰 Components Required

| Component                  | Quantity |
|----------------------------|----------|
| ESP32 Dev Board            | 1        |
| pH Sensor Module (DFRobot) | 1        |
| EC Sensor Module (DFRobot) | 1        |
| DS18B20 Temperature Sensor | 1        |
| 4-Channel Relay Module     | 1        |
| Water Pumps                | 4        |
| Jumper Wires               | As needed |
| Power Supply for Pumps     | 1        |

---

## 🧠 Features

- **Sensor Readings Every 4 Seconds**
  - pH with voltage-to-pH conversion
  - EC with temperature compensation
  - Real-time water temperature

- **Pump Control via Serial**
  - Commands: `'P1'`, `'P2'`, `'P3'`, `'P4'`, `'OFF'`

- **Automatic Calibration Support**
  - Initiated via serial commands from [DFRobot libraries](https://github.com/DFRobot/DFRobot_PH)  
    (e.g., `ENTERPH`, `CALPH`, `EXITPH`)

---

## ⚙️ Pin Configuration

| Component     | ESP32 GPIO |
|---------------|------------|
| DS18B20       | GPIO 23    |
| pH Sensor     | GPIO 35    |
| EC Sensor     | GPIO 34    |
| Relay Pump 1  | GPIO 16    |
| Relay Pump 2  | GPIO 17    |
| Relay Pump 3  | GPIO 18    |
| Relay Pump 4  | GPIO 19    |

> ⚠️ Active LOW Relay: `LOW = OFF`, `HIGH = ON` logic is used here for demonstration.

---

## 🖥️ Serial Commands

Use a Serial Monitor (baud rate: **115200**) to control pumps:

| Command | Action           |
|---------|------------------|
| `P1`    | Toggle Pump 1 ON for 2s, then OFF |
| `P2`    | Toggle Pump 2 ON for 2s, then OFF |
| `P3`    | Toggle Pump 3 ON for 2s, then OFF |
| `P4`    | Toggle Pump 4 ON for 2s, then OFF |
| `OFF`   | Turns OFF all pumps immediately   |

---

## 🧪 Example Serial Output

----- Sensor Readings -----
Temperature: 24.7 °C
pH Voltage: 1620.0000 mV
pH: 6.7320
EC Raw (ADC): 1078
EC Voltage: 1863.7500 mV
EC Value: 1.4870 mS/cm

---

## 🛠️ Setup Notes

- Ensure the **sensors are calibrated** using DFRobot instructions and calibration commands.
- Use an **external 5V power supply** for pumps through relay for safety.
- Use pull-up resistor (4.7kΩ) on DS18B20 data line.

---

## 📁 File Structure

📦 esp32-hydroponic-system
┣ 📜 hydroponic_monitor.ino
┣ 📜 README.md

---

## 📚 References

- [DFRobot pH Library](https://github.com/DFRobot/DFRobot_PH)
- [DFRobot EC Library](https://github.com/DFRobot/DFRobot_EC)
- [DallasTemperature Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)

---

## 📝 License

MIT License – Free for education and experimentation.

---

## 🔧 Future Improvements

- 🌐 Add WiFi and cloud monitoring (e.g. Firebase, Blynk)
- 📈 Visual dashboard via React or web server
- 🔁 Scheduled pump automation based on thresholds
