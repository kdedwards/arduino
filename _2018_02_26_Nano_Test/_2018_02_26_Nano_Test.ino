void setup() {
  // put your setup code here, to run once:
  byte i;
  for(i=0;i<=13;i++){
    pinMode(i,OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(A6,OUTPUT);
  pinMode(A7,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  byte i;
  // put your main code here, to run repeatedly:
  for(i=0;i<=13;i++){
    digitalWrite(i, HIGH);
    delay(100);
  }
  for(i=0;i<=13;i++){
    digitalWrite(i, LOW);
    delay(100);
  }
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,HIGH);
  digitalWrite(A6,HIGH);
  digitalWrite(A7,HIGH);
  delay(1000);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
  digitalWrite(A6,LOW);
  digitalWrite(A7,LOW);
  delay(100);
}
