#include <Arduino.h>
#include <unity.h>
#include "utils.h"

// Unity Assertions Cheat Sheet: https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsCheatSheetSuitableforPrintingandPossiblyFraming.pdf

void setUp() {}
void tearDown() {}

void test_led_builtin_pin_number() {
    TEST_ASSERT_EQUAL(6, LED_BUILTIN);
}

void test_sd_card_available() {
    SD_init();
    File dataFile = SD.open(logFilename, FILE_WRITE);
    TEST_ASSERT_TRUE_MESSAGE(dataFile, "SD card not available");
}

void test_SHT45_sensor()
{
  Adafruit_SHT4x sht4 = SHT45_init();
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);
  TEST_ASSERT_FLOAT_WITHIN_MESSAGE(50.0, 50.0, humidity.relative_humidity, "Relative humidity not reaeding correctly."); // Example expected value
  TEST_ASSERT_FLOAT_WITHIN_MESSAGE(10.0, 25.0, temp.temperature, "Temperature not reading correctly."); // Example expected value
}

void test_K33_ELG_sensor(void)
{
  // Placeholder for K33 ELG sensor test
  TEST_ASSERT_TRUE(true);
}

void test_NGM2611_E13_sensor(void)
{
  // Placeholder for NGM2611 E13 sensor test
  TEST_ASSERT_TRUE(true);
}

void test_LoRa_communication(void)
{
  // Placeholder for LoRa communication test
  TEST_ASSERT_TRUE(true);
}

void test_low_power_mode(void)
{
  // Placeholder for low power mode test
  TEST_ASSERT_TRUE(true);
}

void test_RTC_synchronization(void)
{
  // Placeholder for RTC synchronization test
  TEST_ASSERT_TRUE(true);
}

void test_RTC_alarm_function(void)
{
  // Placeholder for RTC alarm function test
  TEST_ASSERT_TRUE(true);
}

void run_all_tests() {
    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_pin_number);
    RUN_TEST(test_sd_card_available);
    RUN_TEST(test_SHT45_sensor);
    // RUN_TEST(test_data_logging);
    UNITY_END();
}

void setup() {
    delay(2000);
    pinMode(LED_BUILTIN, OUTPUT);
    run_all_tests();
}

void loop() {
    // empty
}
