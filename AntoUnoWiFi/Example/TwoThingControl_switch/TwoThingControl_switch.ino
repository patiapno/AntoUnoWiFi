#include <Wire.h>
#include <Ciao.h>
#include <AntoUnoWiFi.h>

#define channel "your channel1"
#define channe2 "your channel2"
#define key "you key"
#define thing1 "you thing1"
#define thing2 "you thing2"
#define pin 2
#define pin2 3

AntoUnoWiFi Uno(key,thing1,thing2);
void setup() {
  Ciao.begin();
  pinMode(pin,OUTPUT);
  pinMode(pin2,OUTPUT);
  digitalWrite(pin,HIGH);
  digitalWrite(pin2,HIGH);
  delay(200);
}

void loop() {
  Uno.AntoSwitch(pin,channel);
  Ciao.println(Uno.readstring);
  Uno.AntoSwitch(pin2,channe2,2);
  Ciao.println(Uno.readstring);
  delay(1000);
}
