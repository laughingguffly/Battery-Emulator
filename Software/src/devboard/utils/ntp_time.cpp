#include "time.h"
#include <Arduino.h>
#include "ntp_time.h"

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";

// Target time in 24-hour format (modifiable, e.g., 230 for 02:30)
int targetTime = 230;

// A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
// TimeZone rule for Europe/Rome including daylight adjustment rules (optional)
const char *time_zone = "GMT0BST,M3.5.0/1,M10.5.0";  // TimeZone rule for Europe/London including daylight adjustment rules (optional)








unsigned long long getNtpTimeInMillis() {
    configTzTime(time_zone, ntpServer1, ntpServer2);
    struct tm timeinfo;

    // Wait for time to be set
    for (int i = 0; i < 10; i++) {
        if (getLocalTime(&timeinfo)) {
            break;
        }
        delay(1000);
        //Serial.println("Waiting for NTP time...");
    }

    if (!getLocalTime(&timeinfo)) {
        //Serial.println("Failed to obtain time");
        return 0;
    }

    // Convert to milliseconds
    time_t epochTime = mktime(&timeinfo);
    return static_cast<unsigned long long>(epochTime) * 1000;
}


// Function to calculate the difference in milliseconds to the next target time
unsigned long long millisToNextTargetTime(unsigned long long currentMillis, int targetTime) {
    int hour = targetTime / 100;
    int minute = targetTime % 100;

    time_t currentTime = currentMillis / 1000; // Convert milliseconds to seconds
    struct tm* timeinfo = localtime(&currentTime);

    // Set timeinfo to the target time on the next day
    timeinfo->tm_hour = hour;
    timeinfo->tm_min = minute;
    timeinfo->tm_sec = 0;

    // Increment day if the current time is past the target time
    if (mktime(timeinfo) <= currentTime) {
        timeinfo->tm_mday += 1;
    }
}

unsigned long  getTimeOffsetfromNowUntil(int targetTime) {
  unsigned long long timeinMillis = getNtpTimeInMillis();
  if (timeinMillis !=0) {
    return millisToNextTargetTime(timeinMillis, targetTime);
  }
}
