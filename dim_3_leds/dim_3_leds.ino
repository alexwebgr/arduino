const int maxInValue = 1023;
const int maxOutValue = 255;

const int potentPin = A0;
const int lowPin = 3;
const int medPin = 5;
const int hiPin = 9;
const int pins[] = { lowPin, medPin, hiPin };

// sizeof will return the bytes not the items, so we divide by the bytes of the first item
const int pinCount = sizeof(pins) / sizeof(pins[0]);
const float step = (float)maxOutValue / pinCount;

int sensorValue = 0;
int outputValue = 0;

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < pinCount; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  int activePin = 0;

  sensorValue = analogRead(potentPin);
  // outputValue can be with the 0-255 range
  outputValue = map(sensorValue, 0, maxInValue, 0, maxOutValue);

  for(int i = 0; i < pinCount; i++) {
    int rangeMin = (int)(step * i);
    int rangeMax = (int)(step * (i + 1));
    activePin = pins[i];

    if (outputValue <= rangeMin) {
      // we are not there yet -> turn it off
      analogWrite(activePin, 0);
    } else if (outputValue >= rangeMax) {
      // we are past this pin -> full brightness
      analogWrite(activePin, maxOutValue);
    } else {
      // we are within this pin's range -> fade in or out
      int brightness = map(outputValue, rangeMin, rangeMax, 0, maxOutValue);

      analogWrite(activePin, brightness);
    }
  }

  delay(2);
}
