#define sensorPin A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcData = analogRead(sensorPin);
  float voltage = adcData * (5.0 / 1024.0);
  float temperature = voltage * 100;

  Serial.println(temperature);

  delay(2000);
}
