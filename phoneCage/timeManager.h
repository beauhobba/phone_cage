#ifndef timeManager_h
#define timeManager_h

#include "Arduino.h"

/** 
  Class to operate the create a timer. These timers are linked to each actuator to provide ascynhronous abiltities. 
*/ 
class OutputTimer {

  private:
    
  public:
    unsigned long previousMillis;
    long time_interval;
    unsigned long currentMillis;

    unsigned long previousMillis2;
    long time_interval2;
    unsigned long currentMillis2;
    
    /**
      Constructor of the OutputTimer 
    */ 
    OutputTimer();
    
    /**
      Set the timer to a time value 
    */ 
    void setTimer(int timer);
    
    void addTime(int timer);
    
    /**
      Initialises the timer 
    */ 
    void init(); 
    
    /**
      Checks if the timer is available
    */ 
    bool available();
    
    /**
      Checks if the secondary timer is available
    */ 
    bool available2();  
    
    /**
      Sets the secondary timer to a time value 
    */ 
    void setTimer2(int timer);  
};

#endif
