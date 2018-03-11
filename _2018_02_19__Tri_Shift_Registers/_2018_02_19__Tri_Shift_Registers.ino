int SR_CLK=12;       //pin 11 on 54HC595
int SR_LATCH=11;      //pin 12 on 54HC595
int SR_OUTENABLE=10;  //pin 13 on 54HC595
int SR_DATA=9;       //pin 14 on 54HC595
int BUTTON=13;
boolean buttonDown;
boolean run;

void setup() {
  // put your setup code here, to run once:
  pinMode(SR_LATCH, OUTPUT);
  pinMode(SR_CLK, OUTPUT);
  pinMode(SR_OUTENABLE, OUTPUT);
  pinMode(SR_DATA, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(SR_OUTENABLE,LOW);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  run=true;
}

void loadVals(byte ShiftReg1, byte ShiftReg2, byte ShiftReg3){
    digitalWrite(SR_LATCH, LOW);
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, ShiftReg3);
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, ShiftReg2);
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, ShiftReg1);
    digitalWrite(SR_LATCH, HIGH);
    Serial.print("Set: ShiftReg1: ");
    Serial.print(ShiftReg1, BIN);
    Serial.print(" ShiftReg2: ");
    Serial.print(ShiftReg2, BIN);
    Serial.print(" ShiftReg3: ");
    Serial.print(ShiftReg3, BIN);
    Serial.println();
}

void loadSame(byte Value){
    digitalWrite(SR_LATCH, LOW);
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, Value);
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, Value);
    shiftOut(SR_DATA, SR_CLK, MSBFIRST, Value);
    digitalWrite(SR_LATCH, HIGH);
    Serial.print(Value, BIN);
    Serial.println();
}

void loop() {
  for(byte i=0; i <= 255; i++){
    //byte lowByte=i & 0xFF;
    //byte highByte=(i >> 8) & 0xFF;
    //Serial.print("i: ");
    //Serial.print(i);
    //Serial.print(" lb: ");
    //Serial.print(lowByte, BIN);
    //Serial.print(" hb: ");
    //Serial.print(highByte, BIN);
    if(run){
      loadSame(i);
      delay(100);
    }
    buttonDown=digitalRead(BUTTON);
    if(buttonDown){
      //Serial.println("Button Down");
      if(run){run=false;}
      else{run=true;}
      //Serial.println(run);
      digitalWrite(SR_OUTENABLE,HIGH);
      delay(250);
      digitalWrite(SR_OUTENABLE,LOW);
      delay(250);
      digitalWrite(SR_OUTENABLE,HIGH);
      delay(250);
      digitalWrite(SR_OUTENABLE,LOW);
      delay(250);
    }
  }
}
