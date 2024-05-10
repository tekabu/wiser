#define WHEEL_LA 5
#define WHEEL_LB 6
#define WHEEL_RA 8
#define WHEEL_RB 7

void wheel_stop() {
  digitalWrite(WHEEL_LA, HIGH);
  digitalWrite(WHEEL_LB, HIGH);
  digitalWrite(WHEEL_RA, HIGH);
  digitalWrite(WHEEL_RB, HIGH);
}

void wheel_init() {
  pinMode(WHEEL_LA, OUTPUT);
  pinMode(WHEEL_LB, OUTPUT);
  pinMode(WHEEL_RA, OUTPUT);
  pinMode(WHEEL_RB, OUTPUT);
  wheel_stop();
}

void wheel_l_forward() {
  digitalWrite(WHEEL_LA, HIGH);
  digitalWrite(WHEEL_LB, LOW);
}

void wheel_r_forward() {
  digitalWrite(WHEEL_RA, HIGH);
  digitalWrite(WHEEL_RB, LOW);
}

void wheel_l_backward() {
  digitalWrite(WHEEL_LA, LOW);
  digitalWrite(WHEEL_LB, HIGH);
}

void wheel_r_backward() {
  digitalWrite(WHEEL_RA, LOW);
  digitalWrite(WHEEL_RB, HIGH);
}

void wheel_forward() {
  wheel_l_forward();
  wheel_r_forward();
}

void wheel_backward() {
  wheel_l_backward();
  wheel_r_backward();
}

void wheel_left() {
  wheel_l_backward();
  wheel_r_forward();
}

void wheel_right() {
  wheel_l_forward();
  wheel_r_backward();
}
