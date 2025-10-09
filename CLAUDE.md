# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is an Arduino ESP32 project that creates a Nixie-style clock display on a TFT screen. The project targets ESP32 boards with ST7789 320x240 pixel displays, specifically tested on ESP32-2432S028R (Cheap Yellow Display - CYD).

## Hardware Platform
- **Target Board**: ESP32 Dev Module or ESP32-2432S028R (CYD)
- **Display**: ST7789 TFT 320x240 pixels
- **Development Environment**: Arduino IDE 1.8.19 or newer

## Required Libraries
Install these libraries via Arduino Library Manager:
- **TFT_eSPI** by Bodmer (display driver)
- **NTPClient** by Fabrice Weinberg (time synchronization)
- **WiFiManager** by tzapu (WiFi configuration portal) - https://github.com/tzapu/WiFiManager
- **ESP_DoubleResetDetector** by Khoi Hoang (double reset detection) - https://github.com/khoih-prog/ESP_DoubleResetDetector
- **WiFi** (included with ESP32 board package)

## Code Architecture

### Core Components
1. **NixieClockCYD.ino** - Main application file containing:
   - WiFi connection and NTP time synchronization
   - Optimized time tracking using millis() for efficiency
   - Display update logic that only redraws changed digits
   - Hourly NTP sync to maintain accuracy

2. **nixiefont.h** - Font data file containing:
   - RGB565 formatted bitmap arrays for Nixie-style digits (0-9)
   - Colon and dot separators for time display
   - Each digit is 64x106 pixels optimized for the 320x240 screen

### Key Features
- **WiFi Management**: Dynamic WiFi configuration with web portal
- **Double Reset Detection**: Press reset twice to open configuration portal
- **Auto-Reconnection**: Automatically handles WiFi disconnections
- **Efficient Updates**: Only redraws display elements when they change
- **Time Tracking**: Uses millis() timing instead of constant NTP calls
- **Visual Effects**: Blinking colon separator every second
- **Network Optimization**: Syncs with NTP server only once per hour
- **Timezone Support**: Configured for GMT-5 (Bogotá timezone)

## Development Setup
1. Configure ESP32 board support in Arduino IDE:
   - Add board manager URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Install "ESP32 by Espressif Systems"

2. Install required libraries through Library Manager

3. WiFi Configuration (no manual credential setup required):
   - Uses WiFiManager for dynamic WiFi configuration
   - First boot will create "NixieClock-AP" access point
   - Connect to this AP and configure WiFi through web interface
   - Double reset (within 10 seconds) opens configuration portal

## Display Layout
- Screen: 320x240 pixels
- Digit size: 64x106 pixels each
- Layout: HH:MM format with blinking colon
- Positioning: Centered vertically, digits positioned at specific X coordinates

## WiFi Setup Instructions
1. **First Time Setup**:
   - Flash the code to ESP32
   - Device creates "NixieClock-AP" access point
   - Connect to this network and configure WiFi credentials

2. **Reconfigure WiFi**:
   - Press reset button twice within 10 seconds
   - "NixieClock-AP" access point will start
   - Connect and reconfigure credentials

3. **Auto-Recovery**:
   - If WiFi connection is lost, device automatically attempts reconnection
   - Displays status messages on screen during connection attempts

## Timing Configuration
- Double reset detection: 10 seconds window
- NTP sync interval: 1 hour (3600000ms)
- Colon blink interval: 1 second (1000ms)
- Display update check: Every second
- Timezone offset: -5 hours (GMT-5)