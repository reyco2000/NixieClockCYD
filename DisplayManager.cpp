#include "DisplayManager.h"

// CYD Touchscreen pins
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

DisplayManager::DisplayManager() {
  lastHour = -1;
  lastMinute = -1;
  showingDate = false;
  lastTouchState = false;
  touchscreen = nullptr;
}

void DisplayManager::begin() {
  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true);
  tft.invertDisplay(false);
  tft.fillScreen(TFT_BLACK);

  // Initialize touchscreen
  touchscreen = new XPT2046_Bitbang(XPT2046_MOSI, XPT2046_MISO, XPT2046_CLK, XPT2046_CS);
  touchscreen->begin();
  touchscreen->setCalibration(300, 3700, 400, 3700);  // Standard CYD calibration
}

void DisplayManager::clear() {
  tft.fillScreen(TFT_BLACK);
}

void DisplayManager::forceRedraw() {
  lastHour = -1;
  lastMinute = -1;
}

void DisplayManager::drawDigit(uint16_t x, uint8_t digit) {
  if (digit < 10) {
    tft.pushImage(x, Y_POSITION, DIGIT_WIDTH, DIGIT_HEIGHT, (uint16_t*)nixieFont[digit]);
  }
}

void DisplayManager::drawColon(bool visible) {
  uint8_t symbol = visible ? 11 : 10;  // dospuntos : punto
  tft.pushImage(POS_COLON, Y_POSITION, DIGIT_WIDTH, DIGIT_HEIGHT, (uint16_t*)nixieFont[symbol]);
}

void DisplayManager::updateTime(int hours, int minutes) {
  // Only update hour digits if changed
  if (hours != lastHour) {
    drawDigit(POS_HOUR_1, hours / 10);
    drawDigit(POS_HOUR_2, hours % 10);
    lastHour = hours;
  }

  // Only update minute digits if changed
  if (minutes != lastMinute) {
    drawDigit(POS_MIN_1, minutes / 10);
    drawDigit(POS_MIN_2, minutes % 10);
    lastMinute = minutes;

    Serial.printf("Time: %02d:%02d\n", hours, minutes);
  }
}

void DisplayManager::updateColon(bool visible) {
  drawColon(visible);
}

TFT_eSPI* DisplayManager::getTFT() {
  return &tft;
}

bool DisplayManager::checkTouch() {
  if (!touchscreen) return false;

  TouchPoint touch = touchscreen->getTouch();
  bool isTouched = (touch.zRaw > 0);  // Check if screen is being touched

  // Detect touch press (transition from not touched to touched)
  if (isTouched && !lastTouchState) {
    lastTouchState = true;
    showingDate = !showingDate;  // Toggle date display
    return true;
  }

  if (!isTouched) {
    lastTouchState = false;
  }

  return false;
}

bool DisplayManager::isShowingDate() {
  return showingDate;
}

void DisplayManager::displayDate(int day, int month, int year, int dayOfWeek) {
  const char* daysOfWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(3);

  // Display day of week
  tft.setCursor(60, 60);
  if (dayOfWeek >= 0 && dayOfWeek < 7) {
    tft.println(daysOfWeek[dayOfWeek]);
  }

  // Display date
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(3);
  tft.setCursor(40, 110);

  char dateStr[20];
  if (month >= 1 && month <= 12) {
    sprintf(dateStr, "%s %02d, %04d", months[month - 1], day, year);
  } else {
    sprintf(dateStr, "%02d/%02d/%04d", day, month, year);
  }
  tft.println(dateStr);

  // Display instruction
  tft.setTextColor(TFT_DARKGREY);
  tft.setTextSize(1);
  tft.setCursor(80, 200);
  tft.println("Touch to return to clock");
}
