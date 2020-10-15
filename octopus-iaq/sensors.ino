Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

unsigned long lastSensorUpdateMillis = 0;

String sensorOutput;

// ---- Functions ----

void setupSensors() {
    printlnMsg("Neopixel", "Initializing Neopixels");
    strip.begin();
    strip.show(); 
    // Initialize all pixels to 'off'
    strip.setPixelColor(0,0,0,0); // alle aus
    strip.setPixelColor(1,0,0,0);
    strip.show(); 

    delay(1000); // give sensors some time to start up
}

float getVcc () {
  return ESP.getVcc() / 1000.0;
}

// ---- Neopixel Functions ----

void showCalibrationState(int iaqAccuracy) {
  if (iaqAccuracy) {
    strip.setPixelColor(0,strip.Color(0,brightness,0));  
  } else {
    strip.setPixelColor(0,strip.Color(brightness,brightness,0));
  }
  strip.show();
}

void showIAQState(int iaq) {
  if (iaq < 100) {
    strip.setPixelColor(1,strip.Color(0,brightness,0));      
  } else if (iaq < 250) {
    strip.setPixelColor(1,strip.Color(brightness,brightness,0));  
  } else {
    strip.setPixelColor(1,strip.Color(0,brightness,brightness));      
  }
  strip.show();
}

// ---- Pretty-printing Functions ----

void loopSensors() {
    if (millis() - lastSensorUpdateMillis > sensorUpdateRateMS) {
        lastSensorUpdateMillis = millis();
        printSensors();
    }
//    delay(loopDelay);
}

void printSensors () {
    float vcc = getVcc();
    sensorOutput = "vcc=" + String(vcc);
    printlnMsg("Sensors", sensorOutput);
}
