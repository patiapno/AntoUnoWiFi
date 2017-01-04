#include <Wire.h>
#include <Ciao.h>
#include <AntoUnoWiFi.h>

#define key "Your key"
#define thing "Your thing"
AntoUnoWiFi Uno(key,thing);
void setup() {
  Ciao.begin();
}

void loop() {
  Uno.AntoDataService("gas.ulg95.price");
  String a1=Uno.readstring;
  Ciao.println(a1);
  delay(500);
}
