bool testWifi(void) {
  int c = 1;
  // Serial.println("Waiting for Wifi to connect");

  while (c) {
    if (WiFi.status() == WL_CONNECTED) {


      return true;

    }
  }
  return false;
}
