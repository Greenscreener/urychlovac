#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#include <SoftwareSerial.h>

#define rxPin 11
#define txPin 10

// set up a new serial port
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);


void setup() {
  // put your setup code here, to run once:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.flush();
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PatekCERN...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pulse: ?? ms");
  lcd.setCursor(0, 1);
  lcd.print("Speed: ?? m/s");

}

void loop() {
  if (mySerial.available()>0){
    int lenght = mySerial.parseInt(); 
    int speed = mySerial.parseInt(); 
    if (mySerial.read() == '\n') {
      lcd.setCursor(7, 0);
      lcd.print(String(lenght) + " ms ");
      lcd.setCursor(7, 1);
      float speedms = float(2) / (float(speed) / float(1000));
      lcd.print(String(speedms) + " m/s ");
    }
  
  }
  
}
