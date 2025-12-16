#pragma once

#include <SPI.h>
#include <SD.h>
#include "Adafruit_SHT4x.h"
#include <vector>
#include "RTClib.h"

// SD 
extern int chipSelectSD; // SD card chip select pin for SPI
extern String logFilename; 

// RTC 
extern char daysOfTheWeek[7][12];
extern RTC_DS3231 rtc;
extern int CLOCK_INTERRUPT_PIN;

void SD_init();
Adafruit_SHT4x SHT45_init();
void log_data(const std::vector<String>& data, String filename);
void rtc_init(bool setTime);
void rtc_print_time(int mode = 0);
String rtc_get_time(int mode = 0);
void onAlarm();
