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

  if (triggerStatus && pressCount <=10){
    if (millis() - triggerMillis >= 1000/pressCount) {
      triggerMillis = millis();

      for (int i = 0; i < LEDCount; i += 3) {
        int index = LEDIndex + i;
        if (index >= LEDCount) index -= LEDCount;
        digitalWrite(LEDPins[index], LOW);
      }
      
      LEDIndex++;
      if (LEDIndex >= LEDCount) LEDIndex = 0;

      for (int i = 0; i < LEDCount; i += 3) {
        int index = LEDIndex + i;
        if (index >= LEDCount) index -= LEDCount;
        digitalWrite(LEDPins[index], HIGH);
      }
    }
  }
  else {
    pressCount = 0;
    triggerStatus = false;
    for (int j=0; j<LEDCount; j++){
      digitalWrite(LEDPins[j], LOW);
    }
  }
}
