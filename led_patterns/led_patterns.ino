const int pin1 = 3;
const int pin2 = 5;
const int pin3 = 9;
const int pin4 = 10;
const int pin5 = 11;
const int pins[] = { pin1, pin2, pin3, pin4, pin5 };
// sizeof will return the bytes not the items, so we divide by the bytes of the first item
const int pinCount = sizeof(pins) / sizeof(pins[0]);
const int timer = 200;
const int fadeStep = 1;
const int fadeSpeed = 5; // ms delay between updates
const int maxBrightness = 255;
const int totalFadeTime = (maxBrightness / fadeStep) * fadeSpeed;
const int interval = totalFadeTime / 10;
int brightness[] = {0, 0, 0, 0, 0};
int direction[] = {1, 1, 1, 1, 1};  // 1=fading up, -1=fading down
unsigned long previousMillis[] = {0, 0, 0, 0, 0};
unsigned long sequenceStartTime = 0;
unsigned long startDelay[] = {0, interval, interval * 2, interval * 3, interval * 4};  // Staggered starts
bool sequenceActive = false;

void setup() {
  /*
    An unconnected analog pin acts like an antenna, picking up random electromagnetic noise from the environment.
    When you call analogRead() on it, you get an unpredictable value influenced by nearby electrical fields, radio signals,
    and other ambient interference.
    Without randomSeed(), the random() function generates the same sequence every time your Arduino resets because
    it's pseudorandom, it follows a deterministic algorithm. The seed value sets the starting point for that sequence,
    so different seeds produce different sequences.
  */
  randomSeed(analogRead(A1));

  for (int i = 0; i < pinCount; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  fastBlink();
  ping();
  pong();
  pang();
  pingPong();
  randomize();
  groupChaser();
//   fadeChaser();
}

/* Utilities */
void power(int state = LOW) {
  for (int i = 0; i < pinCount; i++) {
    int thisPin = pins[i];

    digitalWrite(thisPin, state);
  }
}

void ping() {
  for (int i = 0; i < pinCount; i++) {
    int thisPin = pins[i];
    int nextPin = pins[i + 1];

    digitalWrite(thisPin, HIGH);
    delay(timer);
    digitalWrite(thisPin, LOW);
    digitalWrite(nextPin, HIGH);
    delay(timer);
    digitalWrite(nextPin, LOW);
  }
}

void pong() {
  for (int i = pinCount; i >= 0; i--) {
    int thisPin = pins[i];
    int nextPin = pins[i - 1];

    digitalWrite(thisPin, HIGH);
    delay(timer);
    digitalWrite(thisPin, LOW);
    digitalWrite(nextPin, HIGH);
    delay(timer);
    digitalWrite(nextPin, LOW);
  }
}

void pang() {
  for (int i = pinCount; i >= 0; i--) {
    int thisPin = pins[i];
    int nextPin = pins[i + 1];

    digitalWrite(thisPin, HIGH);
    delay(timer);
    digitalWrite(thisPin, LOW);
    digitalWrite(nextPin, HIGH);
    delay(timer);
    digitalWrite(nextPin, LOW);
  }
}

/**
  Pattern: Chaser
  1 on
  delay
  1 off
  2 on
  delay
  2 off
  3 on
  delay
  3 off
*/

void chaser() {
  ping();
}
/**
Pattern: Fast blink
all on
delay
all off
*/
void fastBlink() {
  power(HIGH);
  delay(timer);

  power(LOW);
  delay(timer);
}

/**
Pattern: Ping-pong
like chaser but also in reverse
  1 on
  delay
  1 off
  2 on
  delay
  2 off
  3 on
  delay
  3 off
*/

void pingPong() {
  ping();
  delay(timer);
  pong();
  delay(timer);
}

/**
  Pattern: Random
  Flash random LEDs
*/
void randomize() {
  for (int i = 0; i < 13; i++) {
    int randomIndex = random(0, pinCount);

    digitalWrite(pins[randomIndex], HIGH);
    delay(timer);
    digitalWrite(pins[randomIndex], LOW);
  }
}

/**
  Pattern: Group chaser
  divide in groups of 2 and blink them together like the chaser
  pin 1 om
  pin 2 om
  delay
  pin 1 off
  pin 2 off
  pin 3 on
  pin 4 on
  delay
  pin 3 off
  pin 4 off
  pin 5 on
  pin 6 on
  delay
  pin 5 off
  pin 6 off
  delay
*/
void groupChaser() {
  int group_size = 2;
  for (int i = 0; i < pinCount; i += group_size) {
    for (int j = i; j < i + group_size && j < pinCount; j++) {
      digitalWrite(pins[j], HIGH);
    }

    delay(timer);

    for (int j = i; j < i + group_size && j < pinCount; j++) {
      digitalWrite(pins[j], LOW);
    }
  }
}

void fadeChaser() {
  if (!sequenceActive) {
    sequenceStartTime = millis();
    resetSequence();
    sequenceActive = true;
  }

  unsigned long currentMillis = millis();
  bool allDone = true;

  for (int i = 0; i < pinCount; i++) {
    updateLED(i, currentMillis);
    if (brightness[i] > 0 || direction[i] == 1) {
      allDone = false;
    }
  }

  if (allDone) {
    sequenceActive = false;  // Ready for next call
  }
}

void resetSequence() {
  for (int i = 0; i < pinCount; i++) {
    brightness[i] = 0;
    direction[i] = 1;
    previousMillis[i] = 0;
    // startDelay relative to sequence start
    startDelay[i] = sequenceStartTime + (interval * i);
  }
}

void updateLED(int ledIndex, unsigned long currentMillis) {
  if (currentMillis < startDelay[ledIndex]) {
    return;
  }

  if (currentMillis - previousMillis[ledIndex] >= fadeSpeed) {
    previousMillis[ledIndex] = currentMillis;

    // Each LED independently fades
    if (direction[ledIndex] == 1) {
      brightness[ledIndex] += fadeStep;
    } else {
      brightness[ledIndex] -= fadeStep;
    }

    // Each LED independently switches at max
    if (brightness[ledIndex] >= maxBrightness) {
      brightness[ledIndex] = maxBrightness;
      direction[ledIndex] = -1;
    }
    if (brightness[ledIndex] <= 0) {
      brightness[ledIndex] = 0;
    }

    analogWrite(pins[ledIndex], brightness[ledIndex]);
  }
}
