#include <Adafruit_NeoPixel.h>
#include <avr/power.h> // Comment out this line for non-AVR boards (Arduino Due, etc.)


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, 4, NEO_GRB + NEO_KHZ800);

const byte brightness=1;
const uint32_t black=strip.Color(0, 0, 0);
const uint32_t white=strip.Color(255, 255, 255);
const uint32_t red=strip.Color(255, 0, 0);
const uint32_t green=strip.Color(0, 255, 0);
const uint32_t blue=strip.Color(0, 0, 255);
const uint32_t yellow=strip.Color(255, 255, 0);
const uint32_t pink=strip.Color(255,0,255);
const uint32_t teal=strip.Color(0,255,255);

uint32_t stripColors[32]={blue,green,black,red,blue,green,black,red,blue,green,black,red,blue,green,black,red,
                          blue,green,black,red,blue,green,black,red,blue,green,black,red,blue,green,black,red}; //kludge, couldn't ever get strip.getPixelColor() to work nicely with different brightnesses

//uint32_t stripColors[16]={blue,green,black,red,blue,green,black,red,blue,green,black,red,blue,green,black,red};

//uint32_t strip2Colors[16]={blue,blue,black,black,black,black,black,black,red,black,black,black,black,black,black,blue}; //kludge, couldn't ever get strip.getPixelColor() to work nicely with different brightnesses
//uint32_t ring1[16]={blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink};
//uint32_t ring2[16]={red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue};
//uint32_t ring3[16]={green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red};
//uint32_t ring4[16]={pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green};
//uint32_t ringBlack[16]={black,black,black,black,black,black,black,black,black,black,black,black,black,black,black};
//uint32_t ringWhite[16]={white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,};


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip.begin();
  strip.setBrightness(brightness);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  testPattern();
  delay(3000);
  spinCW(8,500);
  //colorWipe(black,20);
  //colorWipe(pink,20);
  //dance();
}

void testPattern(){
  updatePixel(blue,0);
  updatePixel(green,1);
  updatePixel(green,2);
  updatePixel(green,3);
  updatePixel(green,4);
  updatePixel(green,5);
  updatePixel(green,6);
  updatePixel(green,7);
  updatePixel(green,8);
  updatePixel(green,9);
  updatePixel(green,10);
  updatePixel(green,11);
  updatePixel(green,12);
  updatePixel(green,13);
  updatePixel(green,14);
  updatePixel(green,15);

  updatePixel(red,16);
  updatePixel(green,17);
  updatePixel(green,18);
  updatePixel(green,19);
  updatePixel(green,20);
  updatePixel(green,21);
  updatePixel(green,22);
  updatePixel(green,23);
  updatePixel(green,24);
  updatePixel(green,25);
  updatePixel(green,26);
  updatePixel(green,27);
  updatePixel(green,28);
  updatePixel(green,29);
  updatePixel(green,30);
  updatePixel(green,31);
}

void dance(){
  for(int i=0;i<=strip.numPixels();i++){
    updatePixel(blue,i);
    updatePixel(red,strip.numPixels()-i);
    delay(100);
  }
  //spinCW(8,500);
  //for(int i=0;i<strip.numPixels();i++){
  //  updatePixel(green,i);
  //  updatePixel(pink,strip.numPixels()-i);
  //  delay(100);
  //}
}


void updatePixel(uint32_t c, byte numPixel){
      stripColors[numPixel]=c;
      updateStrip();
}

void updateStrip(){
  for(int i=0;i<strip.numPixels();i++){
    strip.setPixelColor(i,stripColors[i]);
  }
  strip.show();
}

void spinCW(int numPositions, int wait){
  for(int i=0;i<numPositions;i++){
    uint32_t tempColor=stripColors[0];
    for(byte j=0; j<strip.numPixels();j++){
        stripColors[j]=stripColors[(j+1)];
    }
    stripColors[strip.numPixels()]=tempColor;
    updateStrip();
    if(wait != 0){delay(wait);}
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      updatePixel(c,i);
      //strip.setPixelColor(i, c);
      //strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
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
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

