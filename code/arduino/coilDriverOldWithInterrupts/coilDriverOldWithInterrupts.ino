#include <SoftwareSerial.h>

int impulsDelay = 1;
int impulsLenght = 100;
int potValue = 1;

unsigned long previouscoil2trigger = 0;
unsigned long lastcoil2trigger = 0;

unsigned long lastdisplaywrite = 0;

int ballspeed = 0;

SoftwareSerial mySerial(4, 5); // RX, TX

void setup() {
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  digitalWrite(7,HIGH);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), impuls1, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), impuls2, FALLING);
  Serial.begin(9600);
  Serial.flush();
  mySerial.begin(4800);
  mySerial.flush();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  potValue = analogRead(A0);
  impulsLenght = map(potValue, 0, 1023, 0, 500);
  if (currentMillis - lastdisplaywrite >= 1000) {
    lastdisplaywrite = currentMillis;
    mySerial.print(impulsLenght);
    mySerial.print(",");
    mySerial.print(lastcoil2trigger-previouscoil2trigger);
    mySerial.print('\n');
  }
}

void impuls1() {
    delay(impulsDelay);
    digitalWrite(7, LOW);
    delay(impulsLenght);
    digitalWrite(7, HIGH);
    Serial.print("1 ");
    Serial.println(millis());
    delay(50);
}

void impuls2() {
    previouscoil2trigger = lastcoil2trigger;
    lastcoil2trigger = millis();
    delay(impulsDelay);
    digitalWrite(8, LOW);
    delay(impulsLenght);
    digitalWrite(8, HIGH);
    Serial.print("2 ");
    Serial.println(millis());
    delay(50);
}
