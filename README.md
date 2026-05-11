# 🚦 Smart Queue Management System — IoT Based Bank Token System

An IoT-powered real-time queue management system for banks that allows customers to book tokens online, displays live queue status on an LCD, and sends real-time notifications — eliminating long physical queues.

---

## 🎯 Problem Statement

Traditional bank queues cause excessive waiting time, overcrowding, and poor customer experience. This system replaces manual token handling with an automated, cloud-connected IoT solution.

---

## 💡 Solution

- Customers book tokens online from home via a web interface
- Token data stored and synced in real time using Firebase
- ESP8266 NodeMCU fetches live queue data and displays it on an LCD inside the bank
- PIR sensor detects customer presence at the counter automatically
- Firebase Cloud Messaging sends notifications when a customer's turn is near

---

## 🛠️ Tech Stack

| Component | Purpose |
|---|---|
| ESP8266 NodeMCU | Main Wi-Fi microcontroller |
| PIR / IR Sensor | Customer presence detection |
| 16x2 LCD Display | Shows current serving token |
| Firebase Realtime Database | Cloud token storage & sync |
| Firebase Cloud Messaging | Customer notifications |
| ThingSpeak | IoT data visualization |
| Arduino IDE | Programming NodeMCU |
| HTML / CSS / JavaScript | Web interface for token booking |

---

## 🏗️ System Architecture

Three-tier architecture:

**Customer Module** → Books token online → Firebase stores data

**Cloud Module (Firebase)** → Real-time sync → Sends FCM notifications

**Bank Module (ESP8266 NodeMCU + LCD)** → Fetches token → Displays on LCD → PIR detects presence

---

## 🚀 How It Works

1. Customer opens web app and books a token
2. Unique token number generated and stored in Firebase
3. ESP8266 NodeMCU fetches current token from Firebase via Wi-Fi
4. LCD screen inside bank displays running token number
5. PIR sensor detects customer at counter
6. Firebase updates queue and notifies next customer
7. ThingSpeak visualizes token and wait time data in real time

---

## 📊 Results

- Successfully implemented and tested hardware prototype
- Real-time token updates visible on Firebase dashboard
- ThingSpeak graphs show token issuance and wait time trends
- Reduced manual effort for bank staff significantly

---

## 🔮 Future Enhancements

- 📱 Android/iOS mobile app for token booking
- 💬 SMS/WhatsApp notifications
- 🎙️ Voice announcement for token numbers
- 🤖 AI-based queue wait time prediction
- 🏦 Multiple counter support

---

## 📁 Files

- `smart_queue_system.ino` — ESP8266 NodeMCU source code
- `iot_project.pdf` — Full project documentation
- `README.md` — Project overview and setup details

---

## 👩‍💻 Author

**Urfiya Libaibe** — CSE '27 @ VVCE Mysore

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=flat&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/urfiya-libaibe-34624b333)

[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=flat&logo=gmail&logoColor=white)](mailto:urfiyalibaibe410@gmail.com)
