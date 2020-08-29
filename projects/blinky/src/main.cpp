#include <Arduino.h>

#define DOTTIME 300

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

const char* morse[] =
{
  "-----",  // 0
  ".----",  // 1
  "..---",  // 2
  "...--",  // 3
  "....-",  // 4
  ".....",  // 5
  "-....",  // 6
  "--...",  // 7
  "---..",  // 8
  "----.",  // 9
};

void sendDot() {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(DOTTIME);
      digitalWrite(LED_BUILTIN, LOW);
}

void sendDash() {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(3 * DOTTIME);
      digitalWrite(LED_BUILTIN, LOW);
}

void nextSymbol() {
      digitalWrite(LED_BUILTIN, LOW);
      delay(DOTTIME);
}

void nextLetter() {
      digitalWrite(LED_BUILTIN, LOW);
      delay(3 * DOTTIME);
}

void nextWord() {
      digitalWrite(LED_BUILTIN, LOW);
      delay(7 * DOTTIME);
}

void send(const char* symbol) {
  for (const char* ch = symbol; *ch; ch++) {
    if (*ch == '.') {
      sendDot();
    } else if (*ch == '-') {
      sendDash();
    }
    nextSymbol();
  }
}

const char* message = "10201";

void loop() {
  // put your main code here, to run repeatedly:
  for (const char* ch = message; *ch; ch++) {
    int num = *ch - '0';
    send(morse[num]);
    nextLetter();
  }
  nextWord();
}
