# Smart-Grain-Storage-System
ESP32-based IoT system for real-time grain storage monitoring

## 📌 Project Overview
This system monitors grain storage conditions in real-time using ESP32 and IoT sensors to detect temperature, humidity, and moisture levels.

## 📖 Working of Smart Grain Storage System

<div align="justify">
The proposed Smart Grain Storage System is an ESP32-based IoT monitoring and control system developed to reduce post-harvest grain losses. It uses multiple sensors, including a temperature and humidity sensor, a moisture sensor, a gas sensor, and a vibration sensor, to continuously monitor the internal storage conditions. These parameters are critical because high temperature, excess humidity, increased moisture content, harmful gas formation, or unusual vibrations can indicate spoilage, fungal growth, or pest activity.
</div>
<div align="justify">
The ESP32 collects and processes all sensor data, compares it with predefined safe threshold values, and automatically controls a relay module when abnormal conditions are detected. The relay activates devices such as an exhaust fan to maintain proper air circulation and stable storage conditions. Real-time readings and system status are displayed on an LCD screen for easy on-site monitoring. In addition, the system provides real-time monitoring and visualization through the Blynk IoT platform via Wi-Fi connectivity, allowing users to access data remotely. This ensures continuous supervision and timely action, making the system efficient and suitable for small- and medium-scale grain storage facilities.
</div>

## 🛠️ Components Used
- ESP32 Microcontroller
- Temperature & Humidity Sensor (DHT11/DHT22)
- Moisture Sensor
- LCD Display
- Blynk IoT App (Mobile Dashboard)
- Buzzer (for alerts)

## 📋 Sensor Thresholds

| Sensor | Parameter | Safe Range | Action Triggered |
|--------|-----------|------------|-----------------|
| DHT22 | Temperature | < 30°C | Fan ON above 30°C |
| DHT22 | Humidity | < 70% | Alert if exceeded |
| Moisture | Grain Moisture | < 14% | Alert if exceeded |
| MQ Gas | Gas Level | < 200 ppm | Alert if exceeded |
| Vibration | Movement | No vibration | LED alert on detect |

## 📷 System Photo
<p align="center">
  <img width="600" alt="System Photo"
  src="https://raw.githubusercontent.com/Bhavyadait10/Smart-Grain-Storage-System/main/images/system_photo.jpg" />
</p>

## 🔌 Circuit Diagram
<p align="center">
  <img width="600" alt="Circuit Diagram"
  src="https://raw.githubusercontent.com/Bhavyadait10/Smart-Grain-Storage-System/main/images/circuit_diagram.jpg" />
</p>

## 📲 Blynk Dashboard
<p align="center">
  <img width="600" alt="Blynk Dashboard"
  src="https://raw.githubusercontent.com/Bhavyadait10/Smart-Grain-Storage-System/main/images/blynk_dashboard.jpg" />
</p>

## 📊 Output
<p align="center">
  <img width="600" alt="Output"
  src="https://raw.githubusercontent.com/Bhavyadait10/Smart-Grain-Storage-System/main/images/output.jpg" />
</p>

## ⚙️ How It Works
1. Sensors collect real-time data
2. ESP32 processes the data
3. Alerts/notifications triggered if values exceed safe limits
4. Data is displayed on LCD /  Data is sent to **Blynk IoT cloud**
5. You can monitor readings live on the **Blynk mobile app**

## 🏆 Awards & Recognition
- 🥈 2nd Place — Avalon Techfest 2026
- 📄 Published in IJCRT 2026
- 🎤 Presented at ICCET 2026

## 📎 Research Publication
**Journal:** International Journal of Creative Research Thoughts (IJCRT), 2026
**Conference:** ICCET 2026 — International Conference on Communication and Emerging Technologies

> One of few undergraduate projects to achieve dual recognition in the same domain.
