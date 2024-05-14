#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>

// Pins declaration
int lcdSDA = D6, lcdSCL = D7, servoPin = D5, trigPin = D1, echoPin = D2, ledGreen = D4, ledRed = D3;

// Sensor Jarak
int distance;
int hitungJarak() {
  int _distance;
  long _duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  _duration = pulseIn(echoPin, HIGH);
  _distance = 0.034 * _duration / 2;

  return _distance;
}

// Servo
Servo servo;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  // LCD
  Wire.begin(lcdSDA, lcdSCL);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Sensor Jarak
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Led
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  // Servo
  servo.attach(servoPin);
}

void loop() {
  distance = hitungJarak();
  Serial.println("Jarak: " + String(distance) + " cm");

  if (distance <= 10) {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    servo.write(90);
    delay(1000);
  } else {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    servo.write(0);
    delay(1000);
  }

  // Display jarak on LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Jarak: ");
  lcd.print(distance);
  lcd.print(" cm");

  delay(100);
}