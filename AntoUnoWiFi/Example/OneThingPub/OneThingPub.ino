#include <Wire.h>
#include <Ciao.h>
#include <AntoUnoWiFi.h>

#define anto_key "You kry"
#define anto_thing1 "You thing"
AntoUnoWiFi Uno(anto_key,anto_thing1);
void setup() {
  Ciao.begin();
}
int i=0;
void loop() {
  i++;
  String a1=String(i);
  
  if(Uno.AntoSetString(a1,"You channel"))
  {
    Ciao.println("Can Write1");
  }
  else if(!(Uno.AntoSetString(a1,"You channel")))
  {
    Ciao.println(Uno.status);
    Ciao.println("Can't Write");
  }
  delay(2000);
}
