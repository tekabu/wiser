#define VOICE_IN_PIN 52
#define VOICE_OUT_PIN 50

void voiceOff() {
  digitalWrite(VOICE_IN_PIN, HIGH);
  digitalWrite(VOICE_OUT_PIN, HIGH);
}

void voiceIn() {
  digitalWrite(VOICE_IN_PIN, LOW);
  delay(5000);
  voiceOff();
}

void voiceOut() {
  digitalWrite(VOICE_OUT_PIN, LOW);
  delay(5000);
  voiceOff();
}

void voiceInit() {
  pinMode(VOICE_IN_PIN, OUTPUT);
  pinMode(VOICE_OUT_PIN, OUTPUT);
  voiceOff();
}