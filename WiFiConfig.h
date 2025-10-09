#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFi.h>
#include <WiFiManager.h>
#include <ESP_DoubleResetDetector.h>
#include <TFT_eSPI.h>

class WiFiConfig {
  public:
    WiFiConfig(TFT_eSPI* display);
    ~WiFiConfig();

    void begin();
    void checkConnection();
    void loop();

    int getTimezoneOffsetSeconds();
    const char* getTimezoneOffset();

  private:
    TFT_eSPI* tft;
    WiFiManager wifiManager;
    DoubleResetDetector* drd;

    char timezoneOffset[6];
    int timezoneOffsetSeconds;
    bool shouldSaveConfig;

    void setupWiFi();
    void displayConfigScreen();
    void displayConnectingScreen();
    void displayConnectedScreen();

    static void saveConfigCallback();
    static void configModeCallback(WiFiManager *myWiFiManager);

    static bool shouldSaveConfigFlag;
};

#endif
