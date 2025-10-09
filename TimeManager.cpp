#include "TimeManager.h"

TimeManager::TimeManager() {
  timeClient = nullptr;
  lastNtpSync = 0;
  baseEpochTime = 0;
  baseMillis = 0;
}

void TimeManager::begin(int timezoneOffsetSeconds) {
  timeClient = new NTPClient(ntpUDP, "pool.ntp.org", timezoneOffsetSeconds, 3600000);
  timeClient->begin();
  sync();
}

void TimeManager::sync() {
  Serial.print("Syncing with NTP...");
  timeClient->update();

  // Store the base time reference
  baseEpochTime = timeClient->getEpochTime();
  baseMillis = millis();
  lastNtpSync = millis();

  Serial.println(" Done!");
  Serial.printf("Synced time: %02d:%02d:%02d\n",
    timeClient->getHours(),
    timeClient->getMinutes(),
    timeClient->getSeconds());
}

void TimeManager::getCurrentTime(int &hours, int &minutes, int &seconds) {
  // Calculate elapsed seconds since last NTP sync
  unsigned long elapsedMillis = millis() - baseMillis;
  unsigned long elapsedSeconds = elapsedMillis / 1000;

  // Calculate current time
  unsigned long currentEpoch = baseEpochTime + elapsedSeconds;

  hours = (currentEpoch % 86400L) / 3600;
  minutes = (currentEpoch % 3600) / 60;
  seconds = currentEpoch % 60;
}

bool TimeManager::shouldSync() {
  return (millis() - lastNtpSync >= NTP_SYNC_INTERVAL);
}

void TimeManager::getCurrentDate(int &day, int &month, int &year, int &dayOfWeek) {
  // Calculate current epoch time
  unsigned long elapsedMillis = millis() - baseMillis;
  unsigned long elapsedSeconds = elapsedMillis / 1000;
  unsigned long currentEpoch = baseEpochTime + elapsedSeconds;

  // Convert epoch to date
  unsigned long days = currentEpoch / 86400L;
  dayOfWeek = (days + 4) % 7;  // January 1, 1970 was Thursday (4)

  year = 1970;
  unsigned long daysInYear;

  while (true) {
    daysInYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 366 : 365;
    if (days >= daysInYear) {
      days -= daysInYear;
      year++;
    } else {
      break;
    }
  }

  // Calculate month and day
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
    daysInMonth[1] = 29;  // Leap year
  }

  month = 1;
  for (int i = 0; i < 12; i++) {
    if (days >= daysInMonth[i]) {
      days -= daysInMonth[i];
      month++;
    } else {
      break;
    }
  }

  day = days + 1;
}
