const byte CLK=10;       //pin 11 on 54HC595
const byte LATCH=9;      //pin 12 on 54HC595
const byte OUTENABLE=8;  //pin 13 on 54HC595
const byte DATA=7;       //pin 14 on 54HC595
const byte BUTTON=13;
boolean buttonDown;
boolean run;

void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(OUTENABLE, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  run=true;
}

void loadVal(byte Address, byte Value){
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLK, MSBFIRST, Value);
    shiftOut(DATA, CLK, MSBFIRST, Address);
    digitalWrite(LATCH, HIGH);
    Serial.print("Set: Address: ");
    Serial.print(Address, BIN);
    Serial.print(" Value: ");
    Serial.print(Value, BIN);
    Serial.println();
}

void loop() {
  for(byte i=0; i <= 255; i++){
    if(run){
      byte myValue=random(0,255);
      loadVal(i,myValue);
    }
    buttonDown=digitalRead(BUTTON);
    if(buttonDown){
      //Serial.println("Button Down");
      if(run){run=false;}
      else{run=true;}
      //Serial.println(run);
      delay(250);
    }
  }
}
