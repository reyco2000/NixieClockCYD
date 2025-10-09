#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeManager {
  public:
    TimeManager();

    void begin(int timezoneOffsetSeconds);
    void sync();
    void getCurrentTime(int &hours, int &minutes, int &seconds);
    void getCurrentDate(int &day, int &month, int &year, int &dayOfWeek);
    bool shouldSync();

  private:
    WiFiUDP ntpUDP;
    NTPClient* timeClient;

    unsigned long lastNtpSync;
    unsigned long baseEpochTime;
    unsigned long baseMillis;

    static const unsigned long NTP_SYNC_INTERVAL = 3600000;  // Sync every hour
};

#endif
