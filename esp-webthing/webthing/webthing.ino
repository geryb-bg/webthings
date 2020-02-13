#include <Arduino.h>
#include "Thing.h"
#include "WebThingAdapter.h"
#include <WiFi.h>

#include "config.h"

#if defined(LED_BUILTIN)
const int builtInLedPin = LED_BUILTIN;
#else
const int builtInLedPin = 5;  // manually configure LED pin
#endif

const int ledPinRich = 15;
const int ledPinGery = 16;

WebThingAdapter* adapter;

const char* ledTypes[] = {"OnOffSwitch", "Light", nullptr};

ThingDevice ledRich("ledRich", "Richard door open warning", ledTypes);
ThingProperty ledOnRich("onRich", "", BOOLEAN, "OnOffProperty");

ThingDevice ledGery("ledGery", "Gery door open warning", ledTypes);
ThingProperty ledOnGery("onGery", "", BOOLEAN, "OnOffProperty");

bool lastOnRich = false;
bool lastOnGery = false;

void setup(void){
  pinMode(builtInLedPin, OUTPUT);
  pinMode(ledPinRich, OUTPUT);
  pinMode(ledPinGery, OUTPUT);
  
  digitalWrite(builtInLedPin, LOW);
  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting to \"");
  Serial.print(WIFI_SSID);
  Serial.println("\"");

  initWifi();

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  initAdapter();
}

void initWifi() {
  digitalWrite(builtInLedPin, HIGH);
  bool blink = true;
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Retry in 5 secs");
    digitalWrite(builtInLedPin, blink ? LOW : HIGH); // active low led
    blink = !blink;
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(5000);
  }
  digitalWrite(builtInLedPin, LOW);
}

void initAdapter() {
  adapter = new WebThingAdapter("w25", WiFi.localIP());

  ledRich.addProperty(&ledOnRich);
  adapter->addDevice(&ledRich);

  ledGery.addProperty(&ledOnGery);
  adapter->addDevice(&ledGery);
  
  adapter->begin();
  
  Serial.println("HTTP server started");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/things/");
  Serial.print(ledRich.id);
  Serial.println(" | ");
  Serial.println(ledGery.id);
}

void loop(void) {
  if (WiFi.status() != WL_CONNECTED) {
    initWifi();
  }
  
  adapter->update();
  
  bool onRich = ledOnRich.getValue().boolean;
  digitalWrite(ledPinRich, onRich ? HIGH : LOW); // active low led
  if (onRich != lastOnRich) {
    Serial.print(ledRich.id);
    Serial.print(": ");
    Serial.println(onRich);
  }
  lastOnRich = onRich;

  bool onGery = ledOnGery.getValue().boolean;
  digitalWrite(ledPinGery, onGery ? HIGH : LOW); // active low led
  if (onGery != lastOnGery) {
    Serial.print(ledGery.id);
    Serial.print(": ");
    Serial.println(onGery);
  }
  lastOnGery = onGery;
}
