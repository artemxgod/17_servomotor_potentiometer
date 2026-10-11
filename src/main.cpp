#include <Arduino.h>
#include <Servo.h>

Servo servo1;
const int pinServo = 8;
const int POT = A0;

int currentAngle = 90;
int targetAngle = 90;

void setup() {
  servo1.attach(pinServo);
  servo1.write(currentAngle);
}

int readPotSmooth() {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(POT);
    delay(2);
  }
  return sum / 10;
}

void loop() {
  int valpot = readPotSmooth();
  int newTarget = map(valpot, 0, 1023, 0, 180);

  if (abs(newTarget - targetAngle) > 1) {
    targetAngle = newTarget;
  }

  if (currentAngle < targetAngle) currentAngle++;
  else if (currentAngle > targetAngle) currentAngle--;

  servo1.write(currentAngle);
  delay(15);
}