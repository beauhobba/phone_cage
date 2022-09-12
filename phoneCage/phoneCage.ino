#include "timeManager.h"
#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>

OutputTimer ButtonTimer;
OutputTimer WorkTimer;

#define PATTING_THRESHOLD 200




// PINS HERE
const int buttonPin = 8;  
const int limitSwitchPin = 10; 
const int neoPixelPin = 11;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);  
static Adafruit_NeoPixel pixels(16, neoPixelPin, NEO_GRB + NEO_KHZ800);

int buttonState = 0;   


void setup() {
  // initialize the LED pin as an output:
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(limitSwitchPin, INPUT);
  Serial.begin(9600);
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  pixels.begin();
  pixels.show();
  pixels.setBrightness(50);
  for(int i=0; i<16; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0, pixels.gamma8(50)));
  }
  pixels.show();
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println(digitalRead(limitSwitchPin));
  long patting =  cs_4_2.capacitiveSensor(30);
  if(patting > PATTING_THRESHOLD){
    Serial.println(patting);
  }
  

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW && ButtonTimer.available()) {
    ButtonTimer.setTimer(4000);
    WorkTimer.addTime(5000);  
    Serial.println("Triggered");
  }


  if(WorkTimer.available()){
    Serial.println("Timer is Available"); 
  }
  
  delay(100);
}
