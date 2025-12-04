#define PIN 12

void setup() {
    pinMode(PIN, OUTPUT);
    Serial.begin(9600);
    Serial.println("Started");
}

void loop() {
    digitalWrite(PIN, HIGH);
    delay(1000);
    digitalWrite(PIN, LOW);
    delay(1000);
}
