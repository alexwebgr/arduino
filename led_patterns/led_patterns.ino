const int greenPin = 3;
const int yellowPin = 5;
const int redPin = 9;
const int pins[] = { greenPin, yellowPin, redPin };
// sizeof will return the bytes not the items, so we divide by the bytes of the first item
const int pinCount = sizeof(pins) / sizeof(pins[0]);
int timer = 200;

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
  fastBlink();
  fastBlink();
  fastBlink();
  pingPong();
  fastBlink();
  fastBlink();
  fastBlink();
  randomize();
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
    delay(100);
    digitalWrite(pins[randomIndex], LOW);
  }
}
