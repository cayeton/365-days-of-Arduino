// [1/365]

const int buttonCount = 2;
const int LEDCount = 8;
int buttonPins[] = {11,12};
const int LEDPins[] = {2,3,4,5,6,7,8,9};
int currentLED = 0;

// States
bool pressStates[buttonCount] = {false};
int currentButtonStates[buttonCount] = {LOW};
int LEDStates[LEDCount] = {LOW};
bool chaserState = false;
int direction = 0;

// Time variables
unsigned long lastDebounce[buttonCount] = {0};
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int blinkInterval = 1000;

// Functions
void leftToRight();
void rightToLeft();

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
  currentMillis = millis();
  for (int i=0; i<buttonCount; i++) {

    currentButtonStates[i] = digitalRead(buttonPins[i]);
    if (currentButtonStates[i] != pressStates[i]){
      lastDebounce[i] = millis();
    }
    
    if ((millis() - lastDebounce[i]) > 50) {
      if (currentButtonStates[i] == LOW && !pressStates[i]) {
        pressStates[i] = true;
        chaserState = true;
        
        direction = i;
        
      }
      else if (currentButtonStates[i] == HIGH && pressStates[i]) {
        pressStates[i] = false;
      }
    }

  }
  if (chaserState && currentMillis - previousMillis >= blinkInterval) {
    previousMillis = currentMillis;

    if (direction) {
      rightToLeft();
    }
    else {
      leftToRight();
    }
  }
}

void leftToRight() {
    
  digitalWrite(LEDPins[currentLED], LOW);
  currentLED ++;
  if (currentLED >= LEDCount){
    currentLED = 0;
  }
  digitalWrite(LEDPins[currentLED], HIGH);
}
void rightToLeft() {

  digitalWrite(LEDPins[currentLED], LOW);
  currentLED --;
  if (currentLED < 0){
    currentLED = 7;
  }
  digitalWrite(LEDPins[currentLED], HIGH);
}
