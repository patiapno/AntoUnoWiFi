#include <Wire.h>
#include <Ciao.h>
#include <AntoUnoWiFi.h>

#define key "h4W4Kk80r4sLcSau0wOtaNHSEuPMUEIJc9xbTPVr"
#define thing "ARDUINO_UNO_WIFI"
#define ch "Auto"
AntoUnoWiFi Uno(key,thing);
void setup() {
  Ciao.begin();
}

void loop() {
  Uno.AntoGetString(ch);
  String a1=Uno.readstring;
  Ciao.println(a1);
  delay(500);
}
