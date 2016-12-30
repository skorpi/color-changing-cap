#include <CapPin.h>

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel onboard = Adafruit_NeoPixel(1, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(11, 10, NEO_GRB + NEO_KHZ800);

#define PINK strip.Color(255,0,128)
#define ORANGE strip.Color(255,75,0)

#define PINK_R_START 255
#define PINK_G_START 0
#define PINK_B_START 128

#define STRIP_THREES_BEGIN    0
#define STRIP_THREES_END      2
#define STRIP_SINGLE_POSITION 3

#define BRIGHTNESS 100

CapPin cPin_r = CapPin(12);
CapPin cPin_g = CapPin(6);
CapPin cPin_b = CapPin(9);

#define THRESH 500

uint8_t pink_r = PINK_R_START;
uint8_t pink_g = PINK_G_START;
uint8_t pink_b = PINK_B_START;

void setup() {
  //Serial.begin(9600);
  //Serial.println("start");
  
  onboard.begin();
  onboard.show();
  strip.begin();
  strip.show();

  onboard.setBrightness(BRIGHTNESS);
  strip.setBrightness(BRIGHTNESS);

  onboard.setPixelColor(0, onboard.Color(pink_r, pink_g, pink_b));
  onboard.show();
    
  strip.setPixelColor(STRIP_SINGLE_POSITION, ORANGE);
  strip.show();

  for(int i=STRIP_THREES_BEGIN;i<=STRIP_THREES_END;i++){
    strip.setPixelColor(i, strip.Color(pink_r, pink_g, pink_b));
    strip.show();
  }
}

void loop() {

  delay(1);
  long total1 = 0;
  long start = millis();
  long total_r =  cPin_r.readPin(2000);
  long total_g =  cPin_g.readPin(2000);
  long total_b =  cPin_b.readPin(2000);

  //Serial.print( millis() - start);
  //Serial.print("total: ");Serial.println(total_r);

  // check if we are sensing that a finger is touching the pad 
  // and that it wasnt already pressed
  
  if (total_r > 500) {
    //Serial.print("total (above thresh): ");Serial.println(total_r);
    changeColorR();
  }
  
  if (total_g > 500) {
    //Serial.print("total (above thresh): ");Serial.println(total_g);
    changeColorG();
  }
    
  if (total_b > 500) {
    //Serial.print("total (above thresh): ");Serial.println(total_b);
    changeColorB();
  }
  
  delay(5);
}

void changeColorR() {
 pink_r = increaseColor(pink_r, 5);
 changeColor();
}
void changeColorG() {
 pink_g = increaseColor(pink_g, 5);
 changeColor();
}
void changeColorB() {
 pink_b = increaseColor(pink_b, 5);
 changeColor();
}

void changeColor() {
 onboard.setPixelColor(0, onboard.Color(pink_r, pink_g, pink_b));
 onboard.show();
 for(int i=STRIP_THREES_BEGIN;i<=STRIP_THREES_END;i++){
    strip.setPixelColor(i, strip.Color(pink_r, pink_g, pink_b));
    strip.show();
 }
}

uint8_t increaseColor(uint8_t old, uint8_t increment) {
  return old + increment;
}

