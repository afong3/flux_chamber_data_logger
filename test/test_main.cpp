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

void test_data_logging() {
    // Clear the file first (optional)
    String testFile = "testFile.txt";
    File clearFile = SD.open(testFile, FILE_WRITE);
    if (clearFile) clearFile.close();

    // Prepare test data
    std::vector<String> testRow = {"Test1", "Test2", "Test3"};
    log_data(testRow, testFile);

    // Read back file
    File dataFile = SD.open(testFile, FILE_READ);
    TEST_ASSERT_TRUE_MESSAGE(dataFile, "Failed to open datalog.txt for reading");

    String fileContent;
    while (dataFile.available()) {
        fileContent += (char)dataFile.read();
    }
    dataFile.close();

   // Split fileContent into lines
    int lastNewline = fileContent.lastIndexOf('\n');
    String lastLine = fileContent.substring(fileContent.lastIndexOf('\n', lastNewline - 1) + 1, lastNewline);

    String expectedLine = "Test1,Test2,Test3";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectedLine.c_str(), lastLine.c_str(), "CSV last line does not match expected output");

    // Delete the test line/file
    bool deleted = SD.remove(testFile);
    TEST_ASSERT_TRUE_MESSAGE(deleted, "Failed to delete log file after test");
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
    RUN_TEST(test_data_logging);
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
