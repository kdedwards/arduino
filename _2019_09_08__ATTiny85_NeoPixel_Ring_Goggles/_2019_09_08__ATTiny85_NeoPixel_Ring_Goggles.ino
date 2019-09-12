#include <Adafruit_NeoPixel.h>
//#include <avr/power.h> // Comment out this line for non-AVR boards (Arduino Due, etc.)


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, 4, NEO_GRB + NEO_KHZ800);

const byte brightness=4; //0-255
const uint32_t black=strip.Color(0,0,0);
const uint32_t white=strip.Color(255,255,255);
const uint32_t red=strip.Color(255,0,0);
const uint32_t green=strip.Color(0,255,0);
const uint32_t blue=strip.Color(0,0,255);
const uint32_t yellow=strip.Color(255,255,0);
const uint32_t pink=strip.Color(255,0,255);
const uint32_t teal=strip.Color(0,255,255);

//uint32_t stripColors[32]={red,pink,black,black,black,black,black,teal,blue,teal,black,black,black,black,black,pink,
//                          red,pink,black,black,black,black,black,teal,blue,teal,black,black,black,black,black,pink};
uint32_t stripColors[32]={red,red,red,red,blue,red,red,red,red,red,red,red,blue,red,red,red,
                          red,red,red,red,blue,red,red,red,red,red,red,red,blue,red,red,red};
                          
//uint32_t ring3[32]={green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red};
//uint32_t ring4[32]={pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green};
//uint32_t ringBlack[32]={black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,
//                        black,black,black,black,black,black,black,black,black,black,black,black,black,black,black,black};
//uint32_t ringWhite[32]={white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,
//                        white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,white};



// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  //#if defined (__AVR_ATtiny85__)
  //  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  //#endif
  // End of trinket special code


  strip.begin();
  strip.setBrightness(brightness);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  spin(8,1,0,100);
  spin(8,2,1,100);
  gearIn(16,25);
  gearOut(16,25);
}

//void testPattern(){
//  for(int i=0;i<32;i++){
//    stripColors[i]=ring1[i];
//  }
//  updateStrip();
//}

void updatePixel(uint32_t c, byte numPixel){
      stripColors[numPixel]=c;
      updateStrip();
}

void updateStrip(){
  for(int i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,stripColors[i]);
  }
  //strip.setBrightness(analogRead(A0));
  strip.show();
}

void spin(byte numPositions, byte ringSelect, bool dir, int wait){

  if(dir == 0){
    for(byte i=0;i<numPositions;i++){
        if(ringSelect==1 || ringSelect==3){
          uint32_t tempColor=stripColors[0];
          for(byte j=0; j<16;j++){
            stripColors[j]=stripColors[(j+1)];
          }
          stripColors[15]=tempColor;
        }
  
      if(ringSelect==2 || ringSelect==3){
        uint32_t tempColor=stripColors[16];
        for(byte j=16; j<32;j++){
            stripColors[j]=stripColors[(j+1)];
        }
        stripColors[31]=tempColor;
      }
      updateStrip();
      if(wait != 0){delay(wait);}
    }
  }

  if(dir == 1){
    for(byte i=0;i<numPositions;i++){
      if(ringSelect==1 || ringSelect==3){
       uint32_t tempColor=stripColors[15];
        for(byte j=15; j>0;j--){
          stripColors[j]=stripColors[(j-1)];
        }
        stripColors[0]=tempColor;
      }
  
      if(ringSelect==2 || ringSelect==3){
        uint32_t tempColor=stripColors[31];
        for(byte j=31; j>16;j--){
          stripColors[j]=stripColors[(j-1)];
        }
        stripColors[16]=tempColor;
      }
      updateStrip();
      if(wait != 0){delay(wait);}
    }
  }
}

void gearIn(byte numPositions, int wait){
    for(byte i=0;i<numPositions;i++){
      uint32_t tempColor=stripColors[0];
      for(byte j=0; j<16;j++){
        stripColors[j]=stripColors[(j+1)];
      }
      stripColors[15]=tempColor;
      
      tempColor=stripColors[31];
      for(byte j=31; j>16;j--){
        stripColors[j]=stripColors[(j-1)];
      }
      stripColors[16]=tempColor;
      
      updateStrip();
      if(wait != 0){delay(wait);}
    }   
}

void gearOut(byte numPositions, int wait){
    for(byte i=0;i<numPositions;i++){
      uint32_t tempColor=stripColors[15];
      for(byte j=15; j>0;j--){
        stripColors[j]=stripColors[(j-1)];
      }
      stripColors[0]=tempColor;
      
      tempColor=stripColors[16];
      for(byte j=16; j<32;j++){
        stripColors[j]=stripColors[(j+1)];
      }
      stripColors[31]=tempColor;
      
      updateStrip();
      if(wait != 0){delay(wait);}
    }   
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      updatePixel(c,i);
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  } else if(WheelPos < 170) {
//    WheelPos -= 85;
//   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  } else {
//   WheelPos -= 170;
//   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//  }
//}
