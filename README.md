\# 🕰️ Nixie Clock for ESP32 CYD



A beautiful Nixie-style clock display for ESP32 with TFT display that syncs time via NTP (Network Time Protocol).



!\[Nixie Clock](https://img.shields.io/badge/Platform-ESP32-blue)

!\[Display](https://img.shields.io/badge/Display-TFT%20320x240-green)

!\[Library](https://img.shields.io/badge/Library-TFT\_\_eSPI-orange)



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

\- \*\*TFT Display\*\* ST7789 320x240 pixels

\- \*\*WiFi Connection\*\*



\### Tested On

\- ESP32-2432S028R (Cheap Yellow Display - CYD)

\- Generic ESP32 Dev Modules with compatible TFT displays



\## 📚 Software Requirements



\### Arduino IDE Setup

1\. \*\*Arduino IDE\*\* 1.8.19 or newer

2\. \*\*ESP32 Board Support\*\*

&nbsp;  - Add to Board Manager URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package\_esp32\_index.json`

&nbsp;  - Install "ESP32 by Espressif Systems"



\### Required Libraries

Install via Arduino Library Manager:

\- \*\*TFT\_eSPI\*\* by Bodmer

\- \*\*NTPClient\*\* by Fabrice Weinberg

\- \*\*WiFi\*\* (included with ESP32 board package)



\## 📦 Installation



\### 1. Clone or Download

```bash

git clone https://github.com/yourusername/nixie-clock-esp32.git

