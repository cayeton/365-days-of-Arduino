const int potPin = A0;
const int LEDPins[] = {8,9,10};

void setup() {
  for (int i=0; i<3; i++) {
    pinMode(LEDPins[i], OUTPUT);
  }
}

void loop() {
  float potValue = analogRead(potPin);

  analogWrite(LEDPins[0], 255 - (potValue / 4));
  analogWrite(LEDPins[2], potValue / 4);
  if (potValue < 512) {
    analogWrite(LEDPins[1], 128 + ((127 * potValue) / 512));
  } else {
    analogWrite(LEDPins[1], 255 - ((127 * (potValue - 512)) / 511));
  }
}
