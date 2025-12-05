const int PIN_REST  = 3;  // Yellow LED
const int PIN_WALK  = 5;  // Green LED
const int PIN_RUN   = 7;  // Red LED

void setup() {
  Serial.begin(9600);
  // Wait for USB serial connection, not suitable for standalone environments
  while (!Serial) { ; }

  pinMode(PIN_REST, OUTPUT);
  pinMode(PIN_WALK, OUTPUT);
  pinMode(PIN_RUN, OUTPUT);

  Serial.println("DUT_READY");
}

void loop() {
  // 1. Only read if data is actually there
  if (Serial.available() > 0) {
    int sensorValue = Serial.parseInt();

    // 2. IMPORTANT: Clear the "newline" character left in the buffer
    // Otherwise the next loop will read it as a 0.
    while (Serial.available() > 0) { Serial.read(); }

    // 3. Ignore timeouts or invalid 0 reads
    if (sensorValue == 0) return;

    if (sensorValue > 0 && sensorValue <= 20) {
      updateState(PIN_REST, "STATE_REST");
    } else if (sensorValue > 20 && sensorValue <= 60) {
      updateState(PIN_WALK, "STATE_WALK");
    } else if (sensorValue > 60) {
      updateState(PIN_RUN, "STATE_RUN");
    }
  }
}

void updateState(int activePin, String stateName) {
  digitalWrite(PIN_REST, LOW);
  digitalWrite(PIN_WALK, LOW);
  digitalWrite(PIN_RUN, LOW);

  digitalWrite(activePin, HIGH);
  Serial.println(stateName);

  delay(200);

  digitalWrite(activePin, LOW);
}
