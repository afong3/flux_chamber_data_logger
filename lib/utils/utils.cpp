#include "utils.h"

#define CLOCK_INTTERUPT_PIN 1


int chipSelectSD = 0;
String logFilename = "datalog.txt";
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
RTC_DS3231 rtc;
int CLOCK_INTERRUPT_PIN = 1;

void SD_init() {
    SD.begin(chipSelectSD);
    Serial.println("SD initialization done.");
}

Adafruit_SHT4x SHT45_init() {
    Adafruit_SHT4x sht4 = Adafruit_SHT4x();
    sht4.begin();
    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    return sht4;
}

void log_data(const std::vector<String>& data, String filename = logFilename) {
    // Open file for appending
    File dataFile = SD.open(filename, FILE_WRITE);
    if (!dataFile) {
        Serial.println("Failed to open file for writing");
        return;
    }

    // Build CSV line
    String line;
    for (size_t i = 0; i < data.size(); ++i) {
        line += data[i];
        if (i < data.size() - 1) {
            line += ",";  // CSV separator
        }
    }
    line += "\n";  // End line

    // Write to file
    dataFile.print(line);
    dataFile.close();
}

void rtc_init(bool setTime) {
    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
    }

    if (setTime) {
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

    pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);

    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    rtc.disable32K();

    rtc.disableAlarm(2);
    rtc.writeSqwPinMode(DS3231_OFF);
}

void rtc_print_time(int mode){
    DateTime now = rtc.now();

    if (mode == 0){ // Include date, day, and time
        Serial.print(now.year(), DEC);
        Serial.print('/');
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.print(now.day(), DEC);
        Serial.print(" (");
        Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
        Serial.print(") ");
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        Serial.print(now.second(), DEC);
        Serial.println();
    }
    else if (mode == 1){ // Include ONLY date
        Serial.print(now.year(), DEC);
        Serial.print('/');
        Serial.print(now.month(), DEC);
        Serial.print('/');
        Serial.print(now.day(), DEC);
        Serial.println();
    }
    else if (mode == 2){ // Include ONLY time
        Serial.print(now.hour(), DEC);
        Serial.print(':');
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        Serial.print(now.second(), DEC);
        Serial.println();
    }
    else if (mode == 3){ // Include ONLY day
        Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
        Serial.println();
    }    
}

String rtc_get_time(int mode) {
    DateTime now = rtc.now();
    String out = "";

    if (mode == 0) {  // date + day + time
        out += String(now.year()) + "/";
        out += String(now.month()) + "/";
        out += String(now.day());
        out += " (";
        out += daysOfTheWeek[now.dayOfTheWeek()];
        out += ") ";
        out += String(now.hour()) + ":";
        out += String(now.minute()) + ":";
        out += String(now.second());
    }
    else if (mode == 1) {  // date only
        out += String(now.year()) + "/";
        out += String(now.month()) + "/";
        out += String(now.day());
    }
    else if (mode == 2) {  // time only
        out += String(now.hour()) + ":";
        out += String(now.minute()) + ":";
        out += String(now.second());
    }
    else if (mode == 3) {  // day of week only
        out += daysOfTheWeek[now.dayOfTheWeek()];
    }

    return out;
}

int rtc_get_hour(){
    DateTime now = rtc.now();

    return now.hour();
}

