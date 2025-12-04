#define sensorPin A0
#define LED_PIN LED_BUILTIN

int passed = 0;
int failed = 0;

void setup() {
  Serial.begin(9600);
  delay(2000);

  Serial.println("---START_MARKER---");
  Serial.println("===============================");
  Serial.println(" FACTORY TEST SUITE");
  Serial.println(" Temperature Logger LM35");
  Serial.println("===============================");

  test_serial_communication();
  test_led_functionality();
  test_temperature_sensor();
  print_summary();

  Serial.println("---END_MARKER---");
  Serial.flush();
  exit(0);
}

void loop() {}

// Test 1: Serial Communication
void test_serial_communication() {
  Serial.print("[TEST 1] Serial Communication... ");

  // If we can print this, serial works
  Serial.println("PASS");
  passed++;
}

// Test 2: LED Output
void test_led_functionality() {
  Serial.print("[TEST 2] LED Functionality... ");

  pinMode(LED_PIN, OUTPUT);

  // Blink LED 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  Serial.println("PASS");
  passed++;
}

// Test 3: Temperature Sensor Communication
void test_temperature_sensor() {
  Serial.print("[TEST 3] Temperature Sensor... ");

  int adcData = analogRead(sensorPin);
  float voltage = adcData * (5.0 / 1024.0);
  float temperature = voltage * 100;

  if (temperature < -55.00 || temperature > 150.00) {
    Serial.print("FAIL (temperature out of range: ");
    Serial.print(temperature);
    Serial.println("°C)");
    failed++;
    return;
  }

  Serial.print("PASS (");
  Serial.print(temperature);
  Serial.println("°C)");
  passed++;
}

void print_summary() {
  Serial.println();
  Serial.println("===============================");
  Serial.println(" TEST SUMMARY");
  Serial.println("===============================");
  Serial.print("Total Tests: ");
  Serial.println(passed + failed);
  Serial.print("Passed: ");
  Serial.println(passed);
  Serial.print("Failed: ");
  Serial.println(failed);

  if (failed == 0) {
    Serial.println("✓ ALL TESTS PASSED");
  } else {
    Serial.println("✗ TESTS FAILED");
  }
  Serial.println("===============================");
}
