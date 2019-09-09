// Requires 16 pixel NeoPixel Ring
#include <Adafruit_NeoPixel.h>
#include <avr/power.h> // Comment out this line for non-AVR boards (Arduino Due, etc.)

#define PIN 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

byte brightness=4;
uint32_t black=strip.Color(0, 0, 0);
uint32_t white=strip.Color(255, 255, 255);
uint32_t red=strip.Color(255, 0, 0);
uint32_t green=strip.Color(0, 255, 0);
uint32_t blue=strip.Color(0, 0, 255);
uint32_t yellow=strip.Color(255, 255, 0);
uint32_t pink=strip.Color(255,0,255);
uint32_t teal=strip.Color(0,255,255);

//uint32_t stripColors[16]={blue,blue,blue,blue,red,green,green,red,blue,blue,blue,blue,red,green,green,red};; //kludge, couldn't ever get strip.getPixelColor() to work nicely with different brightnesses
uint32_t stripColors[16]={blue,blue,black,black,black,black,black,black,red,black,black,black,black,black,black,blue}; //kludge, couldn't ever get strip.getPixelColor() to work nicely with different brightnesses
uint32_t ring1[16]={blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink};
uint32_t ring2[16]={red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue};
uint32_t ring3[16]={green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red};
uint32_t ring4[16]={pink,blue,red,green,pink,blue,red,green,pink,blue,red,green,pink,blue,red,green};
uint32_t ringBlack[16]={black,black,black,black,black,black,black,black,black,black,black,black,black,black,black};
uint32_t ringWhite[16]={white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,white,};

unsigned long now=millis();
unsigned long lastUpdate=millis();
byte color=0;
boolean direction=0;

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  
  strip.begin();
  //strip.setBrightness(brightness);
  strip.show(); // Initialize all pixels to 'off'
  //Serial.begin(9600);
}

void loop(){
  colorWipe(strip.Color(255, 0, 0), 50);
  
  fadeRingtoColor(ringBlack,20);
  delay(1000);
  fadeRingtoColor(ringWhite,20);
  delay(1000);
  rainbowStrip();
  delay(1000);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void tickTock(){
  now=millis();
  if(now > lastUpdate+1000){
      rotateClockwise(16,30);
      lastUpdate=now;
  }
  //Serial.println(now);
  //Serial.println(lastUpdate);
}

void fadeRingtoColor(uint32_t newRing[16],int waitTime){
  unsigned short colorDiff=1;
  while(colorDiff > 0){
    for(byte i=0;i<16;i++){
      byte increment=1;
      byte endRed=newRing[i] >> 16;
      byte endGreen=newRing[i] >> 8;
      byte endBlue=newRing[i];
      byte curRed=getBaseColor(i,0);
      byte curGreen=getBaseColor(i,1);
      byte curBlue=getBaseColor(i,2);
      if(curRed < endRed){
        curRed=curRed+int(abs(curRed-endRed)/2+1);
        //curRed++;
        colorDiff=1;
      }
      else if(curRed > endRed){
        curRed=curRed-int(abs(curRed-endRed)/2+1);
        //curRed--;
        colorDiff=1;
      }
      else{
        colorDiff=0;
      }
      if(curGreen < endGreen){
        curGreen=curGreen+int(abs(curGreen-endGreen)/2+1);
        //curGreen++;
        colorDiff=1;
      }
      else if(curGreen > endGreen){
        curGreen=curGreen-int(abs(curGreen-endGreen)/2+1);
        //curGreen--;
        colorDiff=1;
      }
      if(curBlue < endBlue){
        curBlue=curBlue+int(abs(curBlue-endBlue)/2+1);
        //curBlue++;
        colorDiff=1;
      }
      else if(curBlue > endBlue){
        curBlue=curBlue-int(abs(curBlue-endBlue)/2+1);
        //curBlue--;
        colorDiff=1;
      }
      stripColors[i]=strip.Color(curRed,curGreen,curBlue);
      updateStrip();
    }
    delay(waitTime);
  }
}

void fadePixeltoColor(byte pixel, uint32_t c,int waitTime){
  unsigned short colorDiff=1;
  byte endRed=c >> 16;
  byte endGreen=c >> 8;
  byte endBlue=c;
  while(colorDiff > 0){
    byte curRed=getBaseColor(pixel,0);
    byte curGreen=getBaseColor(pixel,1);
    byte curBlue=getBaseColor(pixel,2);
    if(curRed < endRed){
      curRed++;
      colorDiff=1;
    }
    else if(curRed > endRed){
      curRed--;
      colorDiff=1;
    }
    else{
      colorDiff=0;
    }
    if(curGreen < endGreen){
      curGreen++;
      colorDiff=1;
    }
    else if(curGreen > endGreen){
      curGreen--;
      colorDiff=1;
    }
    if(curBlue < endBlue){
      curBlue++;
      colorDiff=1;
    }
    else if(curBlue > endBlue){
      curBlue--;
      colorDiff=1;
    }
    stripColors[pixel]=strip.Color(curRed,curGreen,curBlue);
    updateStrip();
    delay(waitTime);
  }
}

void printColors(){
  //byte red=stripColors[8] >> 16;
  //byte green=stripColors[8] >> 8;
  //byte blue=stripColors[8];
  //Serial.print("R: ");
  //Serial.print(getBaseColor(8,0));
  //Serial.print("G: ");
  //Serial.print(getBaseColor(8,1));
  //Serial.print("B: ");
  //Serial.println(getBaseColor(8,2));  
}

byte getBaseColor(byte pixel, byte color){
  //color:
  // 0 - RED
  // 1 - BLUE
  // 2 - GREEN
// for (i=0;i<strip.numPixels();i++) {
//      R[i]=(strip.getPixelColor(i) >> 16);
//      G[i]=(strip.getPixelColor(i) >>  8);
//      B[i]=(strip.getPixelColor(i)      );
//    }
//    
  switch (color){
    case 0:
      return stripColors[pixel] >> 16;
      break;
    case 1:
      return stripColors[pixel] >> 8;
      break;
    case 2:
      return stripColors[pixel];
      break;
    default:
      return 0;
  }      
}

void spindownClockwise(short numPlaces, word min_delay, float slowFactor){
  int waitTime;
  for(byte i=1;i<=numPlaces;i++){
    uint32_t tempColor=stripColors[0];
    for(byte j=0; j<16;j++){
        stripColors[j]=stripColors[(j+1) % 16];
    }
    stripColors[15]=tempColor;
    updateStrip();
    float mapVal=2.0*(i/(numPlaces-1.0))-1.0;
    waitTime=min_delay*(slowFactor-1)*pow(mapVal,2)+min_delay;
    delay(waitTime);
  }  
}

void spindownCClockwise(short numPlaces, word min_delay, float slowFactor){
  int waitTime;
  for(byte i=1;i<=numPlaces;i++){
    uint32_t tempColor=stripColors[15];
    for(int j=16; j>0;j--){
        stripColors[j]=stripColors[(j-1) % 16];
    }
    stripColors[0]=tempColor;
    updateStrip();
    float mapVal=2.0*(i/(numPlaces-1.0))-1.0;
    waitTime=min_delay*(slowFactor-1)*pow(mapVal,2)+min_delay;
    delay(waitTime);
  }  
}

void fill(uint32_t c, byte startPixel, byte numPixels){
    for(short i=0;i<numPixels;i++){
      stripColors[(i+startPixel) % 16]=c;
    }
    updateStrip();
}

void brightnessUp(byte newBrightness, short waitTime){
  for(byte i=brightness;i<newBrightness;i++){
    strip.setBrightness(i);
    strip.show();
    delay(waitTime);
  }
  brightness=newBrightness;
}

void brightnessDown(byte newBrightness, short waitTime){
  for(byte i=brightness;i>newBrightness;i--){
    strip.setBrightness(i);
    strip.show();
    delay(waitTime);
  }
  brightness=newBrightness;
}



void swap(byte pixelA, byte pixelB){
  uint32_t tempC=stripColors[pixelA];
  stripColors[pixelA]=stripColors[pixelB];
  stripColors[pixelB]=tempC;
  updateStrip();
}

void rotateClockwise(byte numPlaces, word waitTime){
  for(byte i=1;i<=numPlaces;i++){
    uint32_t tempColor=stripColors[0];
    for(byte j=0; j<16;j++){
        stripColors[j]=stripColors[(j+1) % 16];
    }
    stripColors[15]=tempColor;
    updateStrip();
    delay(waitTime);
  }
}

void rotateCClockwise(byte numPlaces, word waitTime){
  for(byte i=1;i<=numPlaces;i++){
    uint32_t tempColor=stripColors[15];
    for(int j=16; j>0;j--){
        stripColors[j]=stripColors[(j-1) % 16];
    }
    stripColors[0]=tempColor;
    updateStrip();
    delay(waitTime);
  }
}

void fillClockwise(uint32_t c, int startPixel, word waitTime){
  for(int i=16; i>0;i--){
    stripColors[(startPixel+i) % 16]=c;
    updateStrip();
    delay(waitTime);
  }
}

void fillCClockwise(uint32_t c, int startPixel, word waitTime){
  for(int i=0; i<16;i++){
    stripColors[(startPixel+i) % 16]=c;
    updateStrip();
    delay(waitTime);
  }
}

//-- good functions


void setStripColor(uint32_t c){
  for(byte i=0; i<16;i++){
    stripColors[i]=c;
  }
  updateStrip();
}

void updatePixel(uint32_t c, byte numPixel){
      stripColors[numPixel]=c;
      updateStrip();
}

void updateStrip(){
  for(int i=0;i<16;i++){
    strip.setPixelColor(i,stripColors[i]);
  }
  strip.show();
}

void rainbowStrip() {
  uint16_t i, j;
  for(j=0; j<256; j++) { // 5 cycles of all colors on wheel
    //for(i=0; i< strip.numPixels(); i++) {
for(i=0; i< strip.numPixels(); i++) {
      stripColors[i]=Wheel(((i * 256 / strip.numPixels()) + j) & 255);
    }
  }
  updateStrip();
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      stripColors[i]=Wheel(((i * 256 / strip.numPixels()) + j) & 255);
    }
    updateStrip();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

