#include "wheel.h"
#include "trash_bin.h"
#include "sensors.h"
#include "lcd.h"
#include "voice.h"

#define DROP_WAIT_TIME 30       // seconds
#define STOP_WHEEL_DISTANCE 50  // cm
#define WHEEL_BACKWARD_TIME 2   // seconds

void setup() {
  Serial.begin(9600);
  wheel_init();
  trash_bin_init();
  sensors_init();
  lcd_init();
  voiceInit();
  Serial.println("ready");
}

void test_sensor() {
  bool water = object_water();
  bool metal = object_metal();
  bool plastic = object_plastic();
  bool others = object_others();

  Serial.print("water ");
  Serial.print(water);
  Serial.print(" \t");
  Serial.print("metal ");
  Serial.print(metal);
  Serial.print(" \t");
  Serial.print("plastic ");
  Serial.print(plastic);
  Serial.print(" \t");
  Serial.print("others ");
  Serial.print(others);
  Serial.println();
}

void test_motion() {
  bool l_motion = left_motion();
  bool f_motion = front_motion();
  bool r_motion = right_motion();

  Serial.print(l_motion);
  Serial.print("\t");
  Serial.print(f_motion);
  Serial.print("\t");
  Serial.print(r_motion);
  Serial.println();
}

void test_distance() {
  int fd = front_distance();
  int dd = 0; //down_distance();
  Serial.print(fd);
  Serial.print("\t");
  Serial.print(dd);
  Serial.println();
}

void _move() {
  bool l_motion = left_motion();
  bool f_motion = front_motion();
  bool r_motion = right_motion();

  int TURN_DELAY = 1400;
  int WAIT_AFTER_TURN_DELAY = 5000;

  if (l_motion) {
    Serial.println("moving left...");
    wheel_left();
    delay(TURN_DELAY);
    wheel_stop();
    while (left_motion()) {
      delay(10);
    }
    delay(WAIT_AFTER_TURN_DELAY);
    Serial.println("done moving left...");
  } else if (r_motion) {
    Serial.println("moving right...");
    wheel_right();
    delay(TURN_DELAY);
    wheel_stop();
    while (right_motion()) {
      delay(10);
    }
    delay(WAIT_AFTER_TURN_DELAY);
    Serial.println("done moving right...");
  } else if (f_motion) {
    lcd_person();
    _move_front();
    _object();
  }
}

void _move_front() {
  Serial.println("moving front...");
  voiceIn();
  while (true) {
    wheel_forward();
    int fd = front_distance();
    Serial.print("front distance: ");
    Serial.println(fd);
    if (fd <= STOP_WHEEL_DISTANCE) {
      break;
    }
  }
  lcd_clear();
  wheel_stop();
  delay(5000);
}

void _object() {
  Serial.println("waiting for item");
  lcd_wait_drop();
  unsigned long ptime = millis();
  while (true) {
    bool water = object_water();
    bool metal = object_metal();
    bool plastic = object_plastic();
    bool others = object_others();
    bool done = false;

    if (millis() - ptime >= (DROP_WAIT_TIME * 1000)) {
      done = true;
      Serial.println("failed to drop item");
      lcd_no_item();
      delay(2000);
      lcd_sad();
    } else {
      if (water || metal || plastic || others) {
        detect(water, metal, plastic, others);
        done = true;
        Serial.println("success drop item");
        lcd_happy();
      }
    }
    if (done) {
      delay(3000);
      voiceOut();
      lcd_clear();
      wheel_backward();
      delay(WHEEL_BACKWARD_TIME * 1000);
      wheel_stop();
      delay(3000);
      Serial.println("ready");
      break;
    }
  }
}

void loop() {
  // test_sensor(); return;
  // test_distance();
  // x_front(); return;
  _move();

  // test();  // uncomment for testing
}

void test() {
  if (Serial.available()) {
    int i = Serial.readStringUntil('\n').toInt();
    Serial.println(i);
    while (Serial.available()) {
      Serial.read();
      delay(10);
    }
    if (i == 1) {
      wheel_stop();
    } else if (i == 2) {
      wheel_forward();
    } else if (i == 3) {
      wheel_left();
      delay(1400);
      wheel_stop();
    } else if (i == 4) {
      wheel_right();
      delay(1400);
      wheel_stop();
    } else if (i == 5) {
      trash_bin_open();
    } else if (i == 6) {
      trash_bin_close();
    } else if (i == 7) {
      trash_bin_open_close();
      trash_bin_center();
    } else if (i == 8) {
      trash_bin_spin(BIN2_STEPS);
      trash_bin_open_close();
      trash_bin_center();
    } else if (i == 9) {
      trash_bin_spin(BIN3_STEPS);
      trash_bin_open_close();
      trash_bin_center();
    } else if (i == 10) {
      trash_bin_spin(BIN4_STEPS);
      trash_bin_open_close();
      trash_bin_center();
    } else if (i == 11) {
      wheel_l_forward();
    } else if (i == 12) {
      wheel_r_forward();
    }
  }
}

void detect(bool water, bool metal, bool plastic, bool others) {
  if (metal) {
    lcd_metal();
    Serial.println("metal detected");
    trash_bin_center();
    trash_bin_open_close();
    trash_bin_center();
  } else if (plastic) {
    lcd_plastic();
    Serial.println("plastic detected");
    trash_bin_center();
    trash_bin_spin(BIN4_STEPS);
    trash_bin_open_close();
    trash_bin_center();
  } else if (water) {
    lcd_water();
    Serial.println("water detected");
    trash_bin_center();
    trash_bin_spin(BIN3_STEPS);
    trash_bin_open_close();
    trash_bin_center();
  } else if (others) {
    lcd_others();
    Serial.println("others detected");
    trash_bin_center();
    trash_bin_spin(BIN2_STEPS);
    trash_bin_open_close();
    trash_bin_center();
  }
}
