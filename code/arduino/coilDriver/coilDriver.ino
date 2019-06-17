#include <SoftwareSerial.h>

#define coil1pin 10
#define coil2pin 12
#define coil3pin 11

#define swSerialRX 4
#define swSerialTX 5

#define sensor1pin 4
#define sensor2pin 3
#define sensor3pin 2

int impulsDelay = 1;
int impulsLength = 5;
int potValue = 1;

unsigned long previouscoil2trigger = 0;
unsigned long lastcoil2trigger = 0;

unsigned long lastdisplaywrite = 0;

int ballspeed = 0;

SoftwareSerial mySerial(swSerialRX, swSerialTX); // RX, TX

void setup() {

  // coil triggers
  
  pinMode(coil1pin,OUTPUT);
  pinMode(coil2pin,OUTPUT);
  pinMode(coil3pin,OUTPUT);

  // pulling them HIGH
  
  digitalWrite(coil1pin,HIGH);
  digitalWrite(coil2pin,HIGH);
  digitalWrite(coil3pin,HIGH);

  // ball sensors
  
  pinMode(sensor1pin,INPUT_PULLUP);
  pinMode(sensor2pin,INPUT_PULLUP);
  pinMode(sensor3pin,INPUT_PULLUP);

  // preparing Serial connections

  Serial.begin(9600);
  Serial.flush();
  mySerial.begin(4800);
  mySerial.flush();
}

void loop() {
  unsigned long currentMillis = millis();
  // getting the pulse length from the pot
  potValue = analogRead(A0);
  impulsLength = map(potValue, 0, 1023, 0, 100);
  // sending data to the displayDriver every 1s
  if (currentMillis - lastdisplaywrite >= 1000) {
    lastdisplaywrite = currentMillis;
    mySerial.print(impulsLength);
    mySerial.print(",");
    mySerial.print(lastcoil2trigger-previouscoil2trigger);
    mySerial.print('\n');
  }
  // checking if ball detected, if yes then fire the pulse
  if (digitalRead(sensor1pin)) {
    impuls1();
  } else if (digitalRead(sensor2pin)) {
    impuls2();
  } else if (digitalRead(sensor3pin)) {
    impuls3();
  }
}

void impuls1() {
    delay(impulsDelay);
    digitalWrite(coil1pin, LOW);
    delay(impulsLength);
    digitalWrite(coil1pin, HIGH);
    Serial.println(millis());
    delay(50);
}

void impuls2() {
    delay(impulsDelay);
    digitalWrite(coil2pin, LOW);
    delay(impulsLength);
    digitalWrite(coil2pin, HIGH);
    Serial.println(millis());
    delay(50);
    previouscoil2trigger = lastcoil2trigger;
    lastcoil2trigger = millis();
}

void impuls3() {
    delay(impulsDelay);
    digitalWrite(coil3pin, LOW);
    delay(impulsLength);
    digitalWrite(coil3pin, HIGH);
    Serial.println(millis());
    delay(50);
}
