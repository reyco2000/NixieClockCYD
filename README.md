\# 🕰️ Nixie Clock for ESP32 CYD



A beautiful Nixie-style clock display for ESP32 with TFT display that syncs time via NTP (Network Time Protocol).



\## ✨ Features



\- 📡 \*\*Automatic NTP Time Sync\*\* - Syncs with internet time servers
\- 🎨 \*\*Nixie Tube Style Display\*\* - Retro aesthetic with custom font
\- ⚡ \*\*Optimized Performance\*\* - Uses millis() for efficient time tracking
\- 🌍 \*\*Timezone Support\*\* - Configured for Bogotá (GMT-5), easily customizable
\- 💡 \*\*Blinking Colon Separator\*\* - Classic clock animation
\- 🔄 \*\*Smart Updates\*\* - Only redraws digits when they change
\- ⏱️ \*\*Hourly NTP Sync\*\* - Minimal network calls, maximum accuracy



\## 🛠️ Hardware Requirements

\- \*\*ESP32 Development Board\*\* (ESP32 Dev Module or CYD - Cheap Yellow Display)

\- \*\*WiFi Connection\*\*

\### Tested On

\- ESP32-2432S028 (Cheap Yellow Display - CYD)

\- Generic ESP32 Dev Modules with compatible TFT displays



\## 📚 Software Requirements

\### Arduino IDE Setup

1\. \*\*Arduino IDE\*\* 1.8.19

2\. \*\*ESP32 Board Support\*\*

&nbsp;  - Add to Board Manager
URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package\_esp32\_index.json`
(Please use: ESP32 Dev Board  Core Version 2.0.17)

&nbsp;  - Install "ESP32 by Espressif Systems"



\### Required Libraries

Install via Arduino Library Manager:

\- \*\*TFT\_eSPI\*\* by Bodmer version 2.5.43
\- \*\*NTPClient\*\* by Fabrice Weinberg version 3.2.1
\- \*\*WiFi\*\* (included with ESP32 board package)
\- \*\*WiFiConfig\*\* (by Tabahi Tech version 2.2.26)
\- \*\*DoubleResetDetector\*\* (by Stephen Denne version 1.0.3)


\## 📦 Installation



\### 1. Clone or Download

```bash

git clone https://github.com/yourusername/nixie-clock-esp32.git

