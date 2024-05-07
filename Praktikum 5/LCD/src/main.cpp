#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int sdaPin = D2;
int sclPin = D1;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(sdaPin, sclPin);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Prakt PST 2024");
  lcd.setCursor(0, 1);
  lcd.print("Informatika");
}

void loop() {
  // put your main code here, to run repeatedly:
}