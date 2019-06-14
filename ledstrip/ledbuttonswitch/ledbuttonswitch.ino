
#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

// Example to control LPD8806-based RGB LED Modules in a strip

/*****************************************************************************/

// Number of RGB LEDs in strand:
int nLEDs = 12;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;
// mode for chnaging the color
int colorCounter = 1;
//button to change mode
int switchPin = 7;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


int const potPin = A0;    // select the input pin for the potentiometer
int val;      // variable to store the value coming from the sensor
int previousVal = 0;

int r = 255;
int g, b = 0;


// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
//LPD8806 strip = LPD8806(nLEDs);

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif
  pinMode(switchPin ,INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show();
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(switchPin);
  
  // read the value from the sensor
  val = analogRead(potPin);   


  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      Serial.println("off");
    }
    
    delay(50);
  }


  if (val > previousVal){
    Serial.println("increasing in number");   
    goThroughColors(val);
    previousVal = val;
  } else if (val < previousVal) {
//    Serial.println("decreasing in number"); 
     previousVal = val;
  } else {
//     Serial.println("not chnaging colors"); 
  }
 
//  lastButtonState = buttonState;
//       if(buttonPushCounter == 0){
//          colorCustom(strip.Color(127, 127, 127), 50); // white
//       }
//        else if(buttonPushCounter == 1) {
//          colorCustom(strip.Color(127,   0,   0), 50); // Red
//       }
//       else if(buttonPushCounter == 2) {
//          colorCustom(strip.Color(127, 127,   0), 50); // yellow
//       }
//       else if(buttonPushCounter == 3) {
//          colorCustom(strip.Color(  0, 127,   0), 50); // Green
//       }
//       else if(buttonPushCounter == 4) {
//          colorCustom(strip.Color(  0, 127, 127), 50); // Cyan
//       }
//       else if(buttonPushCounter == 5) {
//          colorCustom(strip.Color(  0,   0, 127), 50); // Blue
//       }
//       else if(buttonPushCounter == 6) {
//          colorCustom(strip.Color(127,   0, 127), 50); // Violet
//          buttonPushCounter = 0;
//       }
   
   
     
  // Send a simple pixel chase in...
   // White
  /*
  colorChase(strip.Color(127,   0,   0), 50); // Red
  colorChase(strip.Color(127, 127,   0), 50); // Yellow
  colorChase(strip.Color(  0, 127,   0), 50); // Green
  colorChase(strip.Color(  0, 127, 127), 50); // Cyan
  colorChase(strip.Color(  0,   0, 127), 50); // Blue
  colorChase(strip.Color(127,   0, 127), 50); // Violet

  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(127, 127,   0), 50); // Yellow
  theaterChase(strip.Color(  0, 127,   0), 50); // Green
  theaterChase(strip.Color(  0, 127, 127), 50); // Cyan
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue
  theaterChase(strip.Color(127,   0, 127), 50); // Violet

  // Fill the entire strip with...
  colorWipe(strip.Color(127,   0,   0), 50);  // Red
  colorWipe(strip.Color(  0, 127,   0), 50);  // Green
  colorWipe(strip.Color(  0,   0, 127), 50);  // Blue

  rainbow(10);
  rainbowCycle(0);  // make it go through the cycle fairly fast
  theaterChaseRainbow(50);
  */
}

void goThroughColors(int val){
  if (val <= 384){
    g += 1;
  }  else if (val > 384 && val <= 512 ){
    r -= 1;
  } else if (val > 512 && val <= 640 ){
    b += 1;
  } else if (val > 640 && val <= 768 ){
    g -= 1;
  } else if (val > 768 && val <= 1024 ){
    r += 1;
  }
  colorChase(strip.Color(r,   g,  b), 50); 
      Serial.print("r :"); 
    Serial.println(r); 
    Serial.print("g : "); 
    Serial.println(g); 
    Serial.print("B :"); 
    Serial.println(b); 
    Serial.println(val);  // stop the program for some time

 

};



void colorCustom(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
             // Refresh LED states
    // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}
void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Fill the dots progressively along the strip.
void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 384; j++) {     // cycle all 384 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 384));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}

