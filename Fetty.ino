#include "Fetty.h"

WatchyFetty watchy;

void setup(){
  Serial.begin(115200);
  watchy.init();
}

void loop(){}
