#include "timeManager.h"


OutputTimer ButtonTimer;
OutputTimer WorkTimer;

const int buttonPin = 8;  
int buttonState = 0;   


void setup() {
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW && ButtonTimer.available()) {
    ButtonTimer.setTimer(4000);
    WorkTimer.addTime(5000);  
    Serial.println("Triggered");
  }


  if(WorkTimer.available()){
    Serial.println("Timer is Available"); 
    Serial.println(WorkTimer.time_interval); 
  }
  
  delay(5);
}
