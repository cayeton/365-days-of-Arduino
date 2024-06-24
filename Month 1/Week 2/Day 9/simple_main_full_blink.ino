int main(){
  init();
  pinMode(13, OUTPUT);
  while(1) {
  digitalWrite(13, 1);
  delay(500);
  digitalWrite(13, 0);
  delay(500);
  }
}
