const int piezoPins[7] = {A0, A1, A2, A3, A4, A5, A6};
int threshold = 60;
const int potPin = A7; 

unsigned long lastHitTime[7] = {0};
const unsigned long debounceTime = 100;
const byte midiNotes[7] = {36, 38, 42, 46, 41, 49, 51};

void setup() {
  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(potPin);
  threshold = map(potValue, 0, 1023, 30, 200);

  for (int i = 0; i < 7; i++) {
    int value = analogRead(piezoPins[i]);
    unsigned long now = millis();

    if (value > threshold && (now - lastHitTime[i]) > debounceTime) {
      byte velocity = map(value, threshold, 1023, 10, 127);
      sendNoteOn(midiNotes[i], velocity);
      delay(10);
      sendNoteOff(midiNotes[i]);
      lastHitTime[i] = now;
    }
  }
}

void sendNoteOn(byte note, byte velocity) {
  Serial.write(0x90);
  Serial.write(note);
  Serial.write(velocity);
}

void sendNoteOff(byte note) {
  Serial.write(0x80);
  Serial.write(note);
  Serial.write(0);
}
