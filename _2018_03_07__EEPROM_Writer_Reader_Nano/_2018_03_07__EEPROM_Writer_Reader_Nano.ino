#define BUTTON 13
#define SR_DATA A0
#define SR_LATCH A1
#define SR_CLK A2
#define EEPROM_OE A3
#define EEPROM_WE A4
#define EEPROM_D0 2
#define EEPROM_D7 9
boolean buttonDown;
boolean run=false;
boolean read=false;
String myLetter="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//String myLetter="zZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZzZ";
  

void setup() {
  pinMode(SR_DATA, OUTPUT);                 //SR_DATA pin 14 on 54HC595
  pinMode(SR_LATCH, OUTPUT);                //SR_LATCH pin 12 on 54HC595
  pinMode(SR_CLK, OUTPUT);                  //SR_CLK pin 11 on 54HC595
  pinMode(EEPROM_OE, OUTPUT);               //OE pin 20 on EEPROM 
  pinMode(EEPROM_WE, OUTPUT);               //WE pin 21 on EEPROM
  digitalWrite(EEPROM_OE, HIGH);            //Turn off the EEPROM Output
  digitalWrite(EEPROM_WE, HIGH);            //Turn off Write Enable on EEPROM
  for(byte i=EEPROM_D0;i <= EEPROM_D7;i++){ //Set pins D2-D9 for OUTPUT
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void setAddress(unsigned int Address){
    byte lowByte=Address;                           //Pull out low order byte from unsigned int
    byte highByte=Address >> 8;                     //Pull out high order byte from unsigned int
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, highByte);  //Shift out high order byte so it ends up in the high order shift register
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, lowByte);   //Shift out low order byte so it ends up in the low order shift register
    digitalWrite(SR_LATCH, LOW);                    //Toggle the latch to lock in the state
    digitalWrite(SR_LATCH, HIGH);
}

void setDataPinMode(boolean Mode){ //Set pins D2-D9 for either 0-INPUT or 1-OUTPUT
  if(Mode==0){
    for(byte i=EEPROM_D0;i<=EEPROM_D7;i++){
      pinMode(i, INPUT);
    }
  }
  else if(Mode==1){
    for(byte i=EEPROM_D0;i<=EEPROM_D7;i++){
      pinMode(i, OUTPUT);
    }
  }
}

void setValue(byte Value){  //Set value on pins D2-D9
  for(byte i=EEPROM_D0;i<=EEPROM_D7;i++){
    digitalWrite(i, Value & 1);
    Value=Value >>1;
  }
}

void flashLEDs(byte Pattern){
  setDataPinMode(1);
  switch (Pattern) {
  case 0:         //Wait
    setValue(170);
    delay(500);
    setValue(85);
    delay(500);
    break;
  case 1:         //Start/End
    setValue(128);
    delay(500);
    setValue(1);
    delay(500);
    setValue(128);
    delay(500);
    setValue(1);
    delay(500);
    break;
  case 2:         //Acknowledge
    setValue(255);
    delay(250);
    setValue(0);
    delay(250);
    setValue(255);
    delay(250);
    setValue(0);
    delay(250);
    break;
  default:      //Error
    setValue(255);
    delay(250);
    setValue(0);
    delay(250);
    setValue(1);
    delay(250);
    setValue(128);
    delay(250);
  }
}

void writeValueToAddress(unsigned int Address, byte Value){
  digitalWrite(EEPROM_OE, HIGH);    //Turn off the EEPROM Output
  setAddress(Address);              //Set the address by putting Address on SR
  setValue(Value);                  //Set the value on the data pins
  delay(10);                        //Wait 10ms
  digitalWrite(EEPROM_WE, LOW);     //Turn on write enable on EEPROM
  delayMicroseconds(1);             //Wait 1us
  digitalWrite(EEPROM_WE, HIGH);    //Turn off write enable on EEPROM
  delay(10);
}

byte readAddress(int Address){
  digitalWrite(EEPROM_OE, LOW);   //Turn on the EEPROM Output
  byte value=0;
  for(byte i=EEPROM_D7;i>=EEPROM_D0;i--){
    value+=digitalRead(i);        //Read the value on the pin
    if(i>2){value=value << 1;}    //Shift it into the value
  }
  return value;
}

void fillEEPROM(byte Value){
  setDataPinMode(1);                 //Set the data pins for write/output
  unsigned int i;
  for(i=0;i<=2047;i++){
    writeValueToAddress(i, Value);
  }
}

void fillFirstEEPROM(byte Value, unsigned int Count){
  setDataPinMode(1);               //Set the data pins for write/output
  unsigned int i;
  for(i=0;i<=Count;i++){
    writeValueToAddress(i, Value);
  }
}

void writeLetterToEEPROM(){
  setDataPinMode(1);               //Set the data pins for write/output
  if(myLetter.length() > 2047){ //If data is larger than EEPROM, throw error
    flashLEDs(255);
    return;
  }
  else{
    for(unsigned int i=0;i <= (myLetter.length())-1;i++){
      writeValueToAddress(i, myLetter[i]);
    }
  }
}

void readWholeEEPROM(){
  setDataPinMode(0);                //Set the data pins for read/input
  digitalWrite(EEPROM_OE, LOW);     //Turn on the EEPROM Output
  for(unsigned int j=0;j<=2047;j++){
    setAddress(j);
    byte value=readAddress(j);
    //Serial.print((char)value);
    Serial.print(value, HEX);
    Serial.print(" ");
    if((j+1) % 16 == 0){Serial.println();}  //Newline after 16 values printed
  }
}

void loop() {
  if(run){
    if(read){
      Serial.println("Start read...");
      readWholeEEPROM();
      run=false;
      read=false;
      Serial.println("End read...");
    }
    else{
      flashLEDs(1);       //Flash LEDs in start/stop pattern
      Serial.println("Zeroing EEPROM...");
      //fillEEPROM(0);
      fillFirstEEPROM(0, 64);
      Serial.println("Writing letters..");
      writeLetterToEEPROM();
      flashLEDs(1);       //Flash LEDs in start/stop pattern
      Serial.println("End write...");
      run=false;
      read=true;
      }
  }
  else{
    flashLEDs(0);       //FLash LEDs in waiting pattern
  }
  buttonDown=digitalRead(BUTTON);
  if(buttonDown){
    Serial.println("Button...");
    run=!run;
    flashLEDs(2);       //Flash LEDs in acknowledgement pattern
    delay(1000);
  }
}
