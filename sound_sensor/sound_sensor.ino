const int knockSensor = A0; // Piezo sensor
const int PIN_SOFT = 3;     // Green LED
const int PIN_MED = 5;      // Yellow LED
const int PIN_HI = 7;       // Red LED

const int THRESHOLD_SOFT = 100;
const int THRESHOLD_MED = 250;
const int THRESHOLD_HI = 320;

int debugValue = 0;
bool debugMode = false;

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(PIN_SOFT, OUTPUT);
  pinMode(PIN_MED, OUTPUT);
  pinMode(PIN_HI, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // If we get data, we are definitely in debug mode now
    debugMode = true;

    debugValue = Serial.parseInt();
    while (Serial.available() > 0) { Serial.read(); }

    if (debugValue > 0) {
      processLogic(debugValue);
    }
  }

  if (!debugMode) {
    int reading = analogRead(knockSensor);

    processLogic(reading);
    delay(20);
  }
}

void processLogic(int reading) {
  Serial.print(reading);

  digitalWrite(PIN_SOFT, LOW);
  digitalWrite(PIN_MED, LOW);
  digitalWrite(PIN_HI, LOW);

  if (reading >= THRESHOLD_SOFT) {
    digitalWrite(PIN_SOFT, HIGH);
    Serial.print(" PIN_SOFT");
  }

  if (reading >= THRESHOLD_MED) {
    digitalWrite(PIN_MED, HIGH);
    Serial.print(" + PIN_MED");
  }

  if (reading >= THRESHOLD_HI) {
    digitalWrite(PIN_HI, HIGH);
    Serial.print(" + PIN_HI");
  }

  Serial.println("");
}
