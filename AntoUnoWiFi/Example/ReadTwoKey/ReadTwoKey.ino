#include <Wire.h>
#include <Ciao.h>
#include "AntoUnoWiFi.h"

#define key "YOU KEY"
#define thing1 "THING1"
#define thing2 "THING2"

#define ch1 "ch1"
#define ch2 "ch2"

AntoUnoWiFi Uno(key,thing1,thing2);
void setup() {
  Ciao.begin();
}

void loop() {
  Uno.AntoGetString(ch1);
  String a1=Uno.readstring;
  Ciao.println(a1);
  Uno.AntoGetString(ch2,2);
  String a2=Uno.readstring;
  Ciao.println(a2);
  delay(4000);
}
