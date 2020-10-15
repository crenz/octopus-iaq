/* 
 * This sketch tests the following sensors and actuators: 
 * - WiFi MAC address
 * - ESP8266 power supply
 * - BME280 (if available)
 * - BME680 (if available)
 * - BNE055 (if available)
 * 
 */

#include "settings.h"

WiFiClient wifi;
byte macAddress[6];
char idString[25] = "octopus-iaq-xxxxxxxxxx";

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

   while (!Serial);
    delay(500);
    Serial.println("                             "); // print some spaces to let the Serial Monitor catch up
    Serial.println();
    Serial.println("--- Initializing Octopus --- ");
    printlnMsg("Reset reason", ESP.getResetReason());
    WiFi.macAddress(macAddress);
    printMsg("MAC address", "");
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
        macAddress[0],
        macAddress[1],
        macAddress[2],
        macAddress[3],
        macAddress[4],
        macAddress[5]);
    sprintf(idString, "octopus-iaq-%02x%02x%02x%02x%02x%02x",
        macAddress[0],
        macAddress[1],
        macAddress[2],
        macAddress[3],
        macAddress[4],
        macAddress[5]);
    printlnMsg("ID", idString);
    setupSensors();
    setupBSEC();
    setupWiFi();
    Serial.println();
    Serial.println("--- Sensor Loop --- ");        
}

void loop() {
    loopSensors();
    loopBSEC();
    loopWiFi();
}
