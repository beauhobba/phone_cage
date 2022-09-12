#include "timeManager.h"
#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>

OutputTimer ButtonTimer;
OutputTimer WorkTimer;
OutputTimer PattingTimer;

#define PATTING_THRESHOLD 200
#define RATINGS_CAP 4



// PINS HERE
const int buttonPin = 8;  
const int limitSwitchPin = 10; 
const int neoPixelPin = 11;

const int HAPPINESS [2] = {0, 3};
const int HUNGRYNESS [2] = {4, 7};
const int TIME_LED [2] = {8, 15};
const int PHONE_DOWN_LED [2] = {16, 19}; 


int time_amount = 0; 
int happy = 0;
int hunger = 0; 

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);  
static Adafruit_NeoPixel pixels(20, neoPixelPin, NEO_GRB + NEO_KHZ800);

int buttonState = 0;   
int phone_state = 0; 

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
  pixels.clear(); 
}


void set_led(int i, int j, int r, int g, int b){
  for(int a=i; a<=j; a++) {
    pixels.setPixelColor(a, pixels.Color(r, g, b, pixels.gamma8(50)));
  }
  pixels.show(); 
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // Read the state of the limit switch 
  int limitState = digitalRead(limitSwitchPin); 
  long patting =  cs_4_2.capacitiveSensor(30);

  
  if(patting > PATTING_THRESHOLD){
    if(PattingTimer.available()){
      PattingTimer.setTimer(1500);
      if(happy < RATINGS_CAP){
        happy += 1;
        set_led(HAPPINESS[0], HAPPINESS[0]+happy-1, 0, 100, 100); 
      }
    }
  }
  

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  // Put a timer to allow the user to hold or press
  if (buttonState == LOW && ButtonTimer.available()) {
    ButtonTimer.setTimer(1500);
    
    if(time_amount < 8){
      time_amount += 1;
      set_led(TIME_LED[0], TIME_LED[0]+time_amount-1, 0, 0, 255); 
    }
  }


  // If the phone is in the case then shine green, otherwise shine red
  if(limitState == LOW){
    set_led(PHONE_DOWN_LED[0], PHONE_DOWN_LED[1], 0, 255, 0); 
    // Set the timer once the phone is in
    // Make sure not to restart the timer! 
    if(WorkTimer.available() && phone_state == 0 && time_amount > 0){
      WorkTimer.setTimer(time_amount * 1000); 
      phone_state = 1; 

      // They have done it! Reset
    }else if(WorkTimer.available() && phone_state == 1){
      time_amount = 0; 
      WorkTimer.setTimer(0); 
      set_led(TIME_LED[0], TIME_LED[1], 255, 255, 255); 
      phone_state = 0;
      delay(2000);
      set_led(TIME_LED[0], TIME_LED[1], 0, 0, 0); 

      // Increase Hunger as a Reward 
      if(hunger < RATINGS_CAP){
        hunger += 1;
        set_led(HUNGRYNESS[0], HUNGRYNESS[0]+hunger-1, 255, 20, 147); 
      }
    }

    
  }else{
    set_led(PHONE_DOWN_LED[0], PHONE_DOWN_LED[1], 255, 0, 0); 

    // IF THE USER RELEASES WHEN A TIMER IS SET, RESET THE WHOLE COUNTER. THEY HAVE FAILED 
    if(!WorkTimer.available()){
      WorkTimer.setTimer(0); 
      set_led(TIME_LED[0], TIME_LED[1], 255, 0, 0); 
      delay(2000);
      set_led(TIME_LED[0], TIME_LED[1], 0, 0, 0); 
      time_amount = 0;

      // Decrease Hunger and Happiness as a Punishment 
      if(hunger > 0){
        hunger -= 1;
        set_led(HUNGRYNESS[0], HUNGRYNESS[0]+hunger-1, 255, 20, 147); 
      }
      if(happy > 0){
        happy -= 1;
        set_led(HAPPINESS[0], HAPPINESS[0]+happy-1, 0, 100, 100); 
      }
    }
  }


  // Turn off LEDS as the timer ticks down
  if(!WorkTimer.available()){
    Serial.println("I am not available"); 
    int c_time = (WorkTimer.currentMillis - WorkTimer.previousMillis)/1000; 
    Serial.print("C TIME: ");
    Serial.println(c_time);
    set_led(TIME_LED[0], TIME_LED[0]-1+c_time, 255, 255, 0); 
  }
  
  
  delay(100);
}
