#include "utils.h"

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