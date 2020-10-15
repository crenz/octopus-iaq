#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <Adafruit_Sensor.h>  // Make sure you have the Adafruit Sensor library installed
#include <Adafruit_BNO055.h>  // Make sure you have the Adafruit BNO055 library installed
#include <utility/imumaths.h>
#include <Adafruit_NeoPixel.h> // Make sure you have the Adafruit NeoPixel library installed
#include "wifi_credentials.h"

// ---- Hardware Configuration ----

ADC_MODE(ADC_VCC); // enable reading in VCC of ESP8266

const int uploadRateMS = 10000; // Upload sensor values every x ms

const int sensorUpdateRateMS = 2000; // Print updated sensor value every x ms
const int loopDelay = 0;

const int brightness = 10;

const int temperatureOffset = 4.3f;

#define PIN_NEOPIXEL      13
#define SEALEVELPRESSURE_HPA (1013.25)

// ---- Data structures ----

struct Bno055Values {
    float orientationX;
    float orientationY;
    float orientationZ;
    uint8_t calibrationSys;
    uint8_t calibrationGyro;
    uint8_t calibrationAccel;
    uint8_t calibrationMag;
};
