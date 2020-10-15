bool connected = false;
unsigned long lastUploadMillis = 0;

void setupWiFi() {
    printlnMsg("WiFi", "Connecting to " + String(wifiSSID));
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifiSSID, wifiPassword);
}

void postSensors() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(serverFingerprint);

  HTTPClient https;

  printMsg("WiFi", "Connecting to " + serverUrl + ": "); 
  https.begin(*client, serverUrl);
  https.addHeader("User-Agent", "octopus-iaq/1.0");
  https.addHeader("Authorization", serverAuthorization);
  String data = "octopus-iaq,sensor=" + String(idString) + " " + sensorOutput + "," + bsecOutput;
    Serial.println("data to be sent:\n<<");
    Serial.println(data);
    Serial.println(">>");  
  int httpCode = https.POST(data);

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("POST result %d\n", httpCode);
    
    const String& payload = https.getString();
    Serial.println("received payload:\n<<");
    Serial.println(payload);
    Serial.println(">>");
  } else {
    Serial.printf("error: %s\n", https.errorToString(httpCode).c_str());
  }    
  https.end();
}


void loopWiFi() {
  if (!connected) {
    if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        printMsg("WiFi", "WiFi Connected, IP=");
        Serial.println(WiFi.localIP());
    }
  } else {
    if (WiFi.status() != WL_CONNECTED) {
        connected = false;
        printMsg("WiFi", "Reconnecting to " + String(wifiSSID));
        WiFi.begin(wifiSSID, wifiPassword);
    } else {
      if (millis() - lastUploadMillis > uploadRateMS) {
          lastUploadMillis = millis();
          postSensors();
      }
    }
  }
}
