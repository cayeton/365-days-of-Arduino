const int LED0 = 8;
int button0 = 9;

void setup() {
  Serial.begin(9600);
  pinMode(LED0, OUTPUT);
  pinMode(button0, INPUT_PULLUP);

}

void loop() {

  if (digitalRead(button0)){
    digitalWrite(LED0, LOW);
    Serial.println(digitalRead(button0));
  }
  else{
    digitalWrite(LED0, HIGH);
    Serial.println(digitalRead(button0));
  }

}
