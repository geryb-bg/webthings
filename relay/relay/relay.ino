#include <Arduino.h>

const int relayPin = 16;

#if defined(LED_BUILTIN)
const int builtInLedPin = LED_BUILTIN;
#else
const int builtInLedPin = 5;  // manually configure LED pin
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");

  pinMode(builtInLedPin, OUTPUT);
  digitalWrite(builtInLedPin, LOW);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relayPin, HIGH);
  digitalWrite(builtInLedPin, HIGH);
  Serial.println("on");
  delay(4000);
  digitalWrite(relayPin, LOW);
  digitalWrite(builtInLedPin, LOW);
  Serial.println("off");
  delay(4000);
}
