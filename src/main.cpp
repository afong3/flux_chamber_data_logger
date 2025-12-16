#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "utils.h"
#include <Co2Meter_K33.h>

Co2Meter_K33 k33;

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
  rtc_init(true);

  Wire.begin();
}

void loop() {
  rtc_print_time(0);

  k33.initPoll();
	delay(16000); //wait for sensor to warm up
	double tempValue = k33.readTemp();
	delay(20); 

	double rhValue = k33.readRh();
	delay(20);

	double co2Value = k33.readCo2();
	if (co2Value >= 0) {
		Serial.print("CO2: ");
		Serial.print(co2Value);
		Serial.print("ppm Temp: ");
		Serial.print(tempValue);
		Serial.print("C Rh: ");
		Serial.print(rhValue);
		Serial.println("%");
	}
	else {
		Serial.println("Checksum failed / Communication failure");
		delay(9000);
	}
}
