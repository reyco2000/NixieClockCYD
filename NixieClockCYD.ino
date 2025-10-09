/*******************************************************************************
 * NixieClock (C) 2024 By Reinaldo Torres
 * Code is for Clock that syncs thru NTP, output is display using
 * a Nixie Font for a TFT 320x240 Screen
 * Ported to TFT_eSPI library for CYD 10.5.2025
 * Optimized with millis() time tracking
 * Refactored into modular components for better maintainability
 ******************************************************************************/
#include "DisplayManager.h"
#include "WiFiConfig.h"
#include "TimeManager.h"
#include <WiFi.h>

// Component managers
DisplayManager display;
WiFiConfig* wifiConfig;
TimeManager timeManager;

// Timing constants
const unsigned long COLON_BLINK_INTERVAL = 1000;  // Blink every second

// Display state
unsigned long lastColonBlink = 0;
bool colonVisible = true;

void setup() {
  Serial.begin(115200);
  Serial.println("Nixie Clock - Starting...");

  // Initialize display
  display.begin();

  // Initialize WiFi configuration and setup
  wifiConfig = new WiFiConfig(display.getTFT());
  wifiConfig->begin();

  Serial.println("WiFi setup completed!");

  // Initialize NTP with configured timezone and get initial time
  timeManager.begin(wifiConfig->getTimezoneOffsetSeconds());

  Serial.printf("Timezone configured: GMT%s\n", wifiConfig->getTimezoneOffset());
  Serial.println("Nixie Clock Ready!");
}

void loop() {
  unsigned long currentMillis = millis();

  // Call WiFi configuration loop to maintain double reset detection
  wifiConfig->loop();

  // Check WiFi connection status periodically
  wifiConfig->checkConnection();

  // Sync with NTP server periodically (every hour)
  if (timeManager.shouldSync() && WiFi.status() == WL_CONNECTED) {
    timeManager.sync();
  }

  // Check for touchscreen events
  if (display.checkTouch()) {
    if (display.isShowingDate()) {
      // Switched to date mode - display the date
      int day, month, year, dayOfWeek;
      timeManager.getCurrentDate(day, month, year, dayOfWeek);
      display.displayDate(day, month, year, dayOfWeek);
    } else {
      // Switched back to clock mode - clear screen and force full redraw
      display.clear();
      display.forceRedraw();  // Reset last values to force digit redraw
      lastColonBlink = 0;  // Force immediate colon update
    }
  }

  // Only update time display if not showing date
  if (!display.isShowingDate()) {
    // Update display when minute changes
    static unsigned long lastDisplayUpdate = 0;
    if (currentMillis - lastDisplayUpdate >= 1000) {  // Check every second
      lastDisplayUpdate = currentMillis;

      int hours, minutes, seconds;
      timeManager.getCurrentTime(hours, minutes, seconds);
      display.updateTime(hours, minutes);
    }

    // Blink colon every second
    if (currentMillis - lastColonBlink >= COLON_BLINK_INTERVAL) {
      lastColonBlink = currentMillis;
      colonVisible = !colonVisible;
      display.updateColon(colonVisible);
    }
  }
}
