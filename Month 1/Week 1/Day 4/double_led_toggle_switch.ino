const int buttonCount = 2;
const int LEDCount = 2;
int buttonPins[] = {4,12};
const int LEDPins[] = {8,9};

bool pressStates[buttonCount] = {false};
int currentButtonStates[buttonCount] = {LOW};
int LEDStates[LEDCount] = {LOW};
unsigned long lastDebounce[buttonCount] = {0};

void setup() {

  for (int i=0; i<buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  for (int i=0; i<LEDCount; i++) {
    pinMode(LEDPins[i], OUTPUT);
    digitalWrite(LEDPins[i], LEDStates[i]);
  }
  
}

void loop() {
  for (int i=0; i<buttonCount; i++) {

    currentButtonStates[i] = digitalRead(buttonPins[i]);
    if (currentButtonStates[i] != pressStates[i]){
      lastDebounce[i] = millis();
    }

    if ((millis() - lastDebounce[i]) > 50) {
      if (currentButtonStates[i] == LOW && !pressStates[i]) {
        LEDStates[i] = !LEDStates[i];
        digitalWrite(LEDPins[i], LEDStates[i]);
        pressStates[i] = true;
      }
      else if (currentButtonStates[i] == HIGH && pressStates[i]) {
        pressStates[i] = false;
      }
    }
  }
}
