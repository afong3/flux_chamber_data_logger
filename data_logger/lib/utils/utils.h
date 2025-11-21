#include <SPI.h>
#include <SD.h>
#include "Adafruit_SHT4x.h"
#include <vector>

const int chipSelectSD = 0; // SD card chip select pin for SPI
const String logFilename = "datalog.txt";

void SD_init();
Adafruit_SHT4x SHT45_init();
void log_data(const std::vector<String>& data, String filename);
