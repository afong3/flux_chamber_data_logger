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
