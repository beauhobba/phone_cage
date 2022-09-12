#include "timeManager.h"


OutputTimer::OutputTimer() {
  init();         
}

    void OutputTimer::init() {
        previousMillis = 0;
        time_interval = 0;    
        previousMillis2 = 0;
        time_interval2 = 0;  
    }
    
    bool OutputTimer::available(){
        currentMillis = millis();
        if (currentMillis - previousMillis >= time_interval) {
            previousMillis = currentMillis;
            time_interval = 0; 
            return true;
        }
        return false;
    }
    void OutputTimer::setTimer(int timer){
      time_interval = timer;   
      currentMillis = millis(); 
      previousMillis = currentMillis;
    }
    
    void OutputTimer::addTime(int timer){
      time_interval += timer;   
      currentMillis = millis(); 
      previousMillis = currentMillis;
    }

    bool OutputTimer::available2(){
        currentMillis2 = millis();
        if (currentMillis2 - previousMillis2 >= time_interval2) {
            previousMillis2 = currentMillis2;
            return true;
        }
        return false;
    }
    void OutputTimer::setTimer2(int timer){
      time_interval2 = timer;   
      currentMillis2 = millis(); 
      previousMillis2 = currentMillis;
    }
    
    
