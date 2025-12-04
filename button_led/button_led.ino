#define pushButton 2
#define LED 7

void setup() {
  Serial.begin(9600);

  pinMode(pushButton, INPUT);
  pinMode(LED, OUTPUT);

  // DEBUG
  // for(int pin=0; pin<=13; pin++) {
  //   // no INPUT_PULLDOWN for uno so we revert the logic, 0 is actually the ones that have current
  //   pinMode(pin, INPUT_PULLUP);
  //   Serial.print("Pin "); Serial.print(pin); Serial.print(": "); Serial.println(digitalRead(pin));
  //   delay(500);
  // }
}

void loop() {
  int buttonState = digitalRead(pushButton);

  if (buttonState == 1) {
    Serial.println(buttonState);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  delay(200);
}
