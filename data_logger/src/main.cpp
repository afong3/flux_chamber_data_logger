#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

const int chipSelectSD = 0; // SD card chip select pin for SPI

void SD_debug_suggestions(){
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

void setup() {
  Serial.begin(9600);
  while (!Serial); // BLOCK until serial monitor connects. Bad if you want to deploy
  
  Serial.println("SD Initializing...");
  if (!SD.begin(chipSelectSD)) {
    SD_debug_suggestions();
  }

  Serial.println("SD initialization done.");

}

void loop() {
  String dataString = "Fake reading";

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }  
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
}
