/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <EEPROM.h>


const char* host = "esp8266-webupdate";


ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup(void) {
  EEPROM.begin(512);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));

  }
  //  Serial.print("SSID: ");
  //Serial.println(esid);
  //Serial.println("Reading EEPROM pass");
  String epass = "";
  for (int i = 32; i < 98; ++i)
  {
    epass += char(EEPROM.read(i));

  }
  WiFi.mode(WIFI_OFF);
  if ( esid.length() > 1 ) {
    WiFi.begin(esid.c_str(), epass.c_str());
    if (testWifi()) {}

  } else {
    Serial.println("ERRORE 03: WIFI non configurato!");
  }


  httpUpdater.setup(&httpServer);
  httpServer.begin();


  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
}

void loop(void) {
  httpServer.handleClient();

}
