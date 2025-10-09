#include "WiFiConfig.h"

// Static member initialization
bool WiFiConfig::shouldSaveConfigFlag = false;

WiFiConfig::WiFiConfig(TFT_eSPI* display) {
  tft = display;
  strcpy(timezoneOffset, "-5");  // Default GMT-5
  timezoneOffsetSeconds = -5 * 3600;
  shouldSaveConfig = false;

  // Initialize Double Reset Detector
  drd = new DoubleResetDetector(10, 0x01);  // 10 second timeout, address 0x01
}

WiFiConfig::~WiFiConfig() {
  if (drd) {
    delete drd;
  }
}

void WiFiConfig::saveConfigCallback() {
  Serial.println("Should save config");
  shouldSaveConfigFlag = true;
}

void WiFiConfig::configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void WiFiConfig::displayConfigScreen() {
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_RED, TFT_BLACK);
  tft->setTextSize(3);
  tft->setCursor(20, 40);
  tft->println("⚠ DOUBLE RESET ⚠");

  tft->setTextSize(2);
  tft->setTextColor(TFT_YELLOW, TFT_BLACK);
  tft->setCursor(30, 80);
  tft->println("Entering CONFIG MODE");

  tft->drawLine(20, 110, 300, 110, TFT_DARKGREY);

  tft->setTextSize(2);
  tft->setTextColor(TFT_GREEN, TFT_BLACK);
  tft->setCursor(20, 130);
  tft->println("Connect to:");
  tft->setTextColor(TFT_WHITE, TFT_BLACK);
  tft->setCursor(40, 150);
  tft->println("NixieClock-AP");

  tft->setTextColor(TFT_GREEN, TFT_BLACK);
  tft->setCursor(20, 190);
  tft->println("Open in browser:");
  tft->setCursor(40, 210);
  tft->println("http://192.168.4.1");
}

void WiFiConfig::displayConnectingScreen() {
  tft->fillScreen(TFT_BLACK);
  tft->setTextColor(TFT_YELLOW);
  tft->setTextSize(2);
  tft->setCursor(10, 20);
  tft->println("WiFi Setup");
  tft->setCursor(10, 110);
  tft->println("Connecting...");
}

void WiFiConfig::displayConnectedScreen() {
  tft->fillScreen(TFT_BLACK);
  tft->setCursor(10, 110);
  tft->setTextColor(TFT_GREEN);
  tft->println("WiFi Connected!");
}

void WiFiConfig::setupWiFi() {
  displayConnectingScreen();

  Serial.println("Checking for double reset...");
  bool doubleResetDetected = drd->detectDoubleReset();
  Serial.printf("Double reset detected: %s\n", doubleResetDetected ? "YES" : "NO");

  // Create custom parameter for timezone
  WiFiManagerParameter customTimezone("timezone", "Timezone Offset (e.g., -5 for GMT-5)", timezoneOffset, 6);

  if (doubleResetDetected) {
    displayConfigScreen();

    // Configure WiFiManager for config portal
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.addParameter(&customTimezone);
    wifiManager.setConfigPortalTimeout(0);
    wifiManager.setBreakAfterConfig(true);

    Serial.println("Starting config portal - no timeout");
    if (!wifiManager.startConfigPortal("NixieClock-AP")) {
      Serial.println("Failed to start config portal");
      delay(3000);
      ESP.restart();
      delay(5000);
    }

    // Save timezone configuration if changed
    if (shouldSaveConfigFlag) {
      strcpy(timezoneOffset, customTimezone.getValue());
      timezoneOffsetSeconds = atoi(timezoneOffset) * 3600;
      Serial.printf("Timezone saved: %s (offset: %d seconds)\n", timezoneOffset, timezoneOffsetSeconds);
      shouldSaveConfig = true;
    }

    Serial.println("Config portal exited - WiFi configured!");
    displayConnectedScreen();
    delay(2000);
    tft->fillScreen(TFT_BLACK);
  } else {
    Serial.println("No Double Reset Detected");

    // Configure autoConnect with shorter timeout for normal operation
    wifiManager.setConfigPortalTimeout(180);
    wifiManager.setConnectTimeout(20);

    if (!wifiManager.autoConnect("NixieClock-AP")) {
      Serial.println("Failed to connect and hit timeout");
      tft->setCursor(10, 140);
      tft->println("Failed! Restart");
      delay(3000);
      ESP.restart();
      delay(5000);
    }
  }

  Serial.println("WiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  displayConnectedScreen();
  delay(2000);
  tft->fillScreen(TFT_BLACK);
}

void WiFiConfig::begin() {
  setupWiFi();
}

void WiFiConfig::loop() {
  drd->loop();
}

void WiFiConfig::checkConnection() {
  static unsigned long lastWiFiCheck = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastWiFiCheck >= 30000) {
    lastWiFiCheck = currentMillis;

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi disconnected! Attempting reconnection...");
      tft->fillScreen(TFT_BLACK);
      tft->setTextColor(TFT_RED);
      tft->setTextSize(2);
      tft->setCursor(10, 110);
      tft->println("WiFi Lost!");
      tft->setCursor(10, 140);
      tft->println("Reconnecting...");

      WiFi.reconnect();
      delay(5000);

      if (WiFi.status() != WL_CONNECTED) {
        if (!wifiManager.autoConnect("NixieClock-AP")) {
          Serial.println("Failed to reconnect, restarting...");
          ESP.restart();
        }
      }

      tft->fillScreen(TFT_BLACK);
      Serial.println("WiFi reconnected!");
    }
  }
}

int WiFiConfig::getTimezoneOffsetSeconds() {
  return timezoneOffsetSeconds;
}

const char* WiFiConfig::getTimezoneOffset() {
  return timezoneOffset;
}
