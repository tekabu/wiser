#include "Servo.h"

Servo servo;

#define BIN_SERVO 2
#define BIN_MAGNET 16
#define BIN_DIR 3
#define BIN_STEP 4

#define BIN2_STEPS 350
#define BIN3_STEPS 722
#define BIN4_STEPS 1094

#define BEFORE_BIN_OPEN 1.5 // seconds
#define BEFORE_BIN_CLOSE 3 // seconds
#define AFTER_BIN_CLOSE 1.5 // seconds

#define OPEN_BIN_ANGLE 95

void trash_bin_open() {
  servo.write(OPEN_BIN_ANGLE);
}

void trash_bin_close() {
  servo.write(0);
}

void trash_bin_open_close() {
  delay(BEFORE_BIN_OPEN * 1000);
  trash_bin_open();
  delay(BEFORE_BIN_CLOSE * 1000);
  trash_bin_close();
  delay(AFTER_BIN_CLOSE * 1000);
}

bool trash_bin_is_centered() {
  return digitalRead(BIN_MAGNET);
}

void trash_bin_step_off() {
  digitalWrite(BIN_STEP, LOW);
}

void trash_bin_step() {
  digitalWrite(BIN_DIR, LOW);

  digitalWrite(BIN_STEP, HIGH);
  delayMicroseconds(2000);
  digitalWrite(BIN_STEP, LOW);
  delayMicroseconds(2000);
}

void trash_bin_center() {
  while (!trash_bin_is_centered()) {
    trash_bin_step();
  }
  Serial.println("trash bin centered");
}

void trash_bin_spin(int _steps) {
  int steps = 0;
  while (1) {
    trash_bin_step();
    steps++;
    if (steps >= _steps) break;
  }
}

void trash_bin_init() {
  servo.attach(BIN_SERVO);
  trash_bin_close();

  pinMode(BIN_MAGNET, INPUT);
  pinMode(BIN_DIR, OUTPUT);
  pinMode(BIN_STEP, OUTPUT);

  trash_bin_center();
}
