   
#include "Fetty.h"

#define DARKMODE false

WatchyFetty::WatchyFetty(){} //constructor

void WatchyFetty::handleButtonPress() {
  Serial.println("handleButtonPress");
  uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
  if(wakeupBit & MENU_BTN_MASK) {
    Serial.println("Menu Button Pressed");
    showMenu('0', true);
  } else if (wakeupBit & BACK_BTN_MASK){
    Serial.println("Back Button Pressed");
    showWatchFace(true);
  }
}
void WatchyFetty::init(String datetime){
    Serial.println("In my init");
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause(); //get wake up reason
    Wire.begin(SDA, SCL); //init i2c
    RTC.init();
    switch (wakeup_reason)
    {
        case ESP_SLEEP_WAKEUP_EXT0: //RTC Alarm
            RTC.clearAlarm(); //resets the alarm flag in the RTC
            if(guiState == WATCHFACE_STATE){
                RTC.read(currentTime);
                showWatchFace(true); //partial updates on tick
            }
            break;
        case ESP_SLEEP_WAKEUP_EXT1: //button Press
            handleButtonPress();
            //showMenu('0', true);
            break;
        default: //reset
            RTC.config(datetime);
            //_bmaConfig();
            RTC.read(currentTime);
            showWatchFace(false); //full update on reset
            break;
    }
    deepSleep();
}

void WatchyFetty::drawWatchFace() {
  Serial.println("drawWatchFace");
  display.print("Hello World");
}

void WatchyFetty::showMenu(byte menuIndex, bool partialRefresh) {
    Serial.println("showMenu!");
    display.clearScreen();
    display.init(0,false);
    display.setFullWindow();
    display.fillScreen(GxEPD_BLACK);
    display.print("menu");   
    display.display(true);
}

void WatchyFetty::showFastMenu(byte menuIndex) {
    Serial.println("showMenu!");
    display.setFullWindow();
    display.fillScreen(GxEPD_BLACK);
    display.print("menu");  
}
