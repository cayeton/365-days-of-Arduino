// Pin count
const int LEDCount = 12;
// Input and Output pins
const int buttonPin = A0;
const int LEDPins[] = {4,3,2,7,6,5,8,9,10,11,12,13};
// States
int currentButtonState = LOW;
int pressState = LOW;
unsigned long lastDebounce = 0;
int debounceDelay = 50;
bool triggerStatus = false;
unsigned long triggerMillis = 0;
int pressCount = 0;
// Timing
unsigned long previousMillis = 0;
int ledIndex = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  for (int i=0; i<LEDCount; i++) {
    pinMode(LEDPins[i], OUTPUT);
    digitalWrite(LEDPins[i], LOW);
  }
}

void loop() {

  currentButtonState = digitalRead(buttonPin);
  if (currentButtonState != pressState){
    lastDebounce = millis();
  }
  if (millis()-lastDebounce >= debounceDelay){
    if (currentButtonState == LOW && !pressState) {
      triggerStatus = true;
      pressCount++;
      pressState = true;
    }
    else if (currentButtonState == HIGH && pressState) {
      pressState = false;
      
    }
  }

  if (triggerStatus && pressCount <=4){
    for (int i=0; i<LEDCount; i++) {
      analogWrite(LEDPins[i], 255/pressCount);
    }
  }
  else {
    pressCount = 0;
    triggerStatus = false;
    for (int i=0; i<LEDCount; i++) {
      digitalWrite(LEDPins[i], LOW);
    }
  }
}
