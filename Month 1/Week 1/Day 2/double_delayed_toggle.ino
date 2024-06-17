//[2/365]
// Pin count
const int LEDCount = 6;
const int buttonCount = 3;
// Input and Output pins
const int buttonPins[] = {4, 12};
const int LEDPins[] = {6,5,9,10};
// States
int currentButtonStates[buttonCount] = {LOW};
int pressStates[buttonCount] = {LOW};
unsigned long lastDebounce[buttonCount] = {0};
int debounceDelay = 50;
bool triggerStatus[buttonCount] = {false};
unsigned long triggerMillis[buttonCount] = {0};

void setup() {
  for (int i=0; i<buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  // put your setup code here, to run once:
  for (int i=0; i<LEDCount; i++) {
    pinMode(LEDPins[i], OUTPUT);
    digitalWrite(LEDPins[i], LOW);
  }
}

void loop() {
  for (int i=0; i<buttonCount; i++){
    currentButtonStates[i] = digitalRead(buttonPins[i]);
    if (currentButtonStates[i] != pressStates[i]){
      lastDebounce[i] = millis();
    }
    if (millis()-lastDebounce[i] >= debounceDelay){
      if (currentButtonStates[i] == LOW && !pressStates[i]) {
        triggerStatus[i] = !triggerStatus[i];
        pressStates[i] = true;
        triggerMillis[i] = millis();
      }
      else if (currentButtonStates[i] == HIGH && pressStates[i]) {
        pressStates[i] = false;
        
      }
    }

    if (triggerStatus[i]){
      digitalWrite(LEDPins[i*2], HIGH);
      // Serial.println(millis() - triggerMillis);
      if (millis() - triggerMillis[i] >= 3000) {
        digitalWrite(LEDPins[i*2+1], HIGH);
      }
    }
    else {
      for (int j=0; j<2; j++){
        digitalWrite(LEDPins[i*2+j], LOW);
      }
    }

  }
}
