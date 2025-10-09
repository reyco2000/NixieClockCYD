# 🕰️ Nixie Clock for ESP32 CYD

A beautiful retro-style Nixie tube clock display for ESP32 with TFT display, featuring automatic time synchronization via NTP (Network Time Protocol).

---

## ✨ Features

- 📡 **Automatic NTP Time Sync** - Connects to internet time servers for accurate timekeeping
- 🎨 **Nixie Tube Style Display** - Authentic retro aesthetic with custom font rendering
- 🌍 **Timezone Support** - Pre-configured for Bogotá (GMT-5), easily customizable for any timezone
- 🔄 **Smart Display Updates** - Only redraws digits when values change to reduce flicker
- ⏱️ **Hourly NTP Sync** - Maintains accuracy with minimal network calls

---

## 🛠️ Hardware Requirements

### Required Components

- ESP32 Development Board (ESP32 Dev Module or CYD variant)
- TFT Display (integrated in CYD or compatible external display)
- WiFi connection for NTP synchronization

### Tested Devices

- ✅ ESP32-2432S028 (Cheap Yellow Display - CYD)

---

## 📚 Software Requirements

### Arduino IDE Configuration

**Arduino IDE Version:** 1.8.19 or newer

**ESP32 Board Support:**
1. Open Arduino IDE
2. Go to File → Preferences
3. Add this URL to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to Tools → Board → Boards Manager
5. Search for "ESP32" and install **ESP32 by Espressif Systems**
6. **Important:** Use Core Version 2.0.17

### Required Libraries

Install these libraries via Arduino Library Manager (Sketch → Include Library → Manage Libraries):

| Library | Author | Version | Purpose |
|---------|--------|---------|---------|
| TFT_eSPI | Bodmer | 2.5.43 | Display driver |
| NTPClient | Fabrice Weinberg | 3.2.1 | Time synchronization |
| WiFiConfig | Tabahi Tech | 2.2.26 | WiFi configuration |
| DoubleResetDetector | Stephen Denne | 1.0.3 | Configuration portal trigger |
| WiFi | Espressif | Built-in | Network connectivity |

---

## 📦 Installation

### Step 1: Clone the Repository

```bash
git clone https://github.com/reyco2000/nixie-clock-esp32.git
cd nixie-clock-esp32
```

### Step 2: Configure TFT_eSPI Library

1. Locate the TFT_eSPI library folder:
   - **Windows:** `Documents/Arduino/libraries/TFT_eSPI`
   - **macOS:** `~/Documents/Arduino/libraries/TFT_eSPI`
   - **Linux:** `~/Arduino/libraries/TFT_eSPI`

2. Edit `User_Setup.h` or `User_Setup_Select.h` according to your display configuration

### Step 3: Configure WiFi

First-time setup uses WiFiConfig portal:
1. Upload the sketch to your ESP32
2. Double-press the reset button within 10 seconds
3. Connect to the WiFi AP created by the device (name: "ESP32-Clock-Setup")
4. Configure your WiFi credentials in the web portal
5. The device will automatically reconnect on subsequent boots

### Step 4: Upload the Code

1. Open `nixie-clock-esp32.ino` in Arduino IDE
2. Select your board: Tools → Board → ESP32 Dev Module (or your specific board)
3. Select the correct COM port: Tools → Port
4. Click Upload

---


## 🚀 Usage

Once configured and running:

1. **Initial Sync:** The clock will sync with NTP servers on boot
2. **Automatic Updates:** Time is updated every second using `millis()` for precision
3. **Hourly Sync:** NTP resynchronization occurs every hour to maintain accuracy
4. **WiFi Recovery:** If WiFi disconnects, the device will attempt to reconnect automatically

---


## 📝 License

This project is open source and available under the MIT License.

---

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📧 Contact

For questions or suggestions, please open an issue on GitHub.

---

## 🙏 Acknowledgments

- **Bodmer** for the excellent TFT_eSPI library
- **Fabrice Weinberg** for the NTPClient library
- The ESP32 community for continuous support and resources
