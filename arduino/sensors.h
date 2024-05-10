#define SENSOR_WATER 17
#define SENSOR_METAL 9
#define SENSOR_IR 18
#define SENSOR_PLASTIC 10
#define SENSOR_FRONT_MOTION 24
#define SENSOR_FRONT_ECHO 11
#define SENSOR_FRONT_TRIG 12
#define SENSOR_DOWN_ECHO 15
#define SENSOR_DOWN_TRIG 14
#define SENSOR_RIGHT_MOTION 26
#define SENSOR_LEFT_MOTION 28

void sensors_init() {
  pinMode(SENSOR_WATER, INPUT);
  pinMode(SENSOR_METAL, INPUT_PULLUP);
  pinMode(SENSOR_IR, INPUT);
  pinMode(SENSOR_PLASTIC, INPUT_PULLUP);
  pinMode(SENSOR_FRONT_MOTION, INPUT);
  pinMode(SENSOR_FRONT_ECHO, INPUT);
  pinMode(SENSOR_FRONT_TRIG, OUTPUT);
  pinMode(SENSOR_DOWN_ECHO, INPUT);
  pinMode(SENSOR_DOWN_TRIG, OUTPUT);
  pinMode(SENSOR_LEFT_MOTION, INPUT);
  pinMode(SENSOR_RIGHT_MOTION, INPUT);
}

bool object_water() {
  return digitalRead(SENSOR_WATER) ? false : true;
}

bool object_metal() {
  return digitalRead(SENSOR_METAL) ? true : false;
}

bool object_plastic() {
  return digitalRead(SENSOR_PLASTIC) ? false : true;
}

bool object_others() {
  return digitalRead(SENSOR_IR) ? false : true;
}

bool front_motion() {
  return digitalRead(SENSOR_FRONT_MOTION) ? true : false;
}

bool left_motion() {
  return digitalRead(SENSOR_LEFT_MOTION) ? true : false;
}

bool right_motion() {
  return digitalRead(SENSOR_RIGHT_MOTION) ? true : false;
}

int front_distance() {
  digitalWrite(SENSOR_FRONT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR_FRONT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_FRONT_TRIG, LOW);
  long duration = pulseIn(SENSOR_FRONT_ECHO, HIGH);
  int distance = duration * 0.034 / 2;
  if (distance <= 0) {
    distance = 300;
  }
  // Serial.print("front distance: ");
  // Serial.println(distance);
  return distance;
}

int down_distance() {
  digitalWrite(SENSOR_DOWN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR_DOWN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_DOWN_TRIG, LOW);
  long duration = pulseIn(SENSOR_DOWN_ECHO, HIGH);
  int distance = duration * 0.034 / 2;
  if (distance <= 0) {
    distance = 300;
  }
  // Serial.print("down distance: ");
  // Serial.println(distance);
  return distance;
}
