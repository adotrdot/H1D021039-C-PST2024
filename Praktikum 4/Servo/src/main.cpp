#include <Arduino.h>
#include <Servo.h>

int servoPin = D4;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(90);

  for (int pos = 0; pos <= 180; pos++) {
    servo.write(pos);
    delay(15);
  }

  for (int pos = 180; pos >= 0; pos--) {
    servo.write(pos);
    delay(15);
  }
}