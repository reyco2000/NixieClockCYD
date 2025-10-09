#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <TFT_eSPI.h>
#include <XPT2046_Bitbang.h>
#include "nixiefont.h"

class DisplayManager {
  public:
    DisplayManager();

    void begin();
    void updateTime(int hours, int minutes);
    void updateColon(bool visible);
    void clear();
    void forceRedraw();
    void displayDate(int day, int month, int year, int dayOfWeek);
    bool checkTouch();
    bool isShowingDate();

    TFT_eSPI* getTFT();  // Allow access to TFT for WiFiConfig

  private:
    TFT_eSPI tft;
    XPT2046_Bitbang* touchscreen;

    bool showingDate;
    bool lastTouchState;

    const unsigned char* nixieFont[12] = {
      numero_0, numero_1, numero_2, numero_3, numero_4,
      numero_5, numero_6, numero_7, numero_8, numero_9,
      punto, dospuntos
    };

    // Screen layout constants
    static const uint8_t SCREEN_WIDTH = 320;
    static const uint8_t SCREEN_HEIGHT = 240;
    static const uint8_t DIGIT_WIDTH = 64;
    static const uint8_t DIGIT_HEIGHT = 106;
    static const uint8_t Y_POSITION = (SCREEN_HEIGHT - DIGIT_HEIGHT) / 2;

    // Digit positions
    static const uint16_t POS_HOUR_1 = 0;
    static const uint16_t POS_HOUR_2 = 64;
    static const uint16_t POS_COLON = 128;
    static const uint16_t POS_MIN_1 = 192;
    static const uint16_t POS_MIN_2 = 256;

    // Last displayed values to avoid unnecessary redraws
    int lastHour;
    int lastMinute;

    void drawDigit(uint16_t x, uint8_t digit);
    void drawColon(bool visible);
};

#endif
