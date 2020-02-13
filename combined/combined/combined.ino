#include <Arduino.h>
#include "Thing.h"
#include "WebThingAdapter.h"
#include <WiFi.h>

#include "config.h"

const int doorSensorPinRich = 15;
const int relayPinRich = 16;

const int doorSensorPinGery = 2;
const int relayPinGery = 4;

#if defined(LED_BUILTIN)
const int builtInLedPin = LED_BUILTIN;
#else
const int builtInLedPin = 5;
#endif

WebThingAdapter* adapter;

const char* sensorTypes[] = {"OnOffSwitch", "DoorSensor", nullptr};

ThingDevice sensorRich("sensorRich", "Richard garage door", sensorTypes);
ThingProperty doorOpenRich("open", "Whether the door is open (on) or closed (off)", BOOLEAN, "OnOffProperty");

ThingDevice sensorGery("sensorGery", "Gery garage door", sensorTypes);
ThingProperty doorOpenGery("open", "Whether the door is open (on) or closed (off)", BOOLEAN, "OnOffProperty");

const char* relayTypes[] = {"OnOffSwitch", "RelaySensor", nullptr};

ThingDevice relayRich("relayRich", "Open/Close Richard's garage door", relayTypes);
ThingProperty closeDoorRich("close", "Close the door by turning the relay on", BOOLEAN, "OnOffProperty");

ThingDevice relayGery("relayGery", "Open/Close Gery's garage door", relayTypes);
ThingProperty closeDoorGery("close", "Close the door by turning the relay on", BOOLEAN, "OnOffProperty");

void setup() {
  Serial.begin(115200);
  Serial.println("");

  pinMode(builtInLedPin, OUTPUT);
  digitalWrite(builtInLedPin, LOW);
  pinMode(doorSensorPinRich, INPUT);
  pinMode(relayPinRich, OUTPUT);
  pinMode(doorSensorPinGery, INPUT);
  pinMode(relayPinGery, OUTPUT);

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
  adapter = new WebThingAdapter("Things", WiFi.localIP());
  
  sensorRich.addProperty(&doorOpenRich);
  adapter->addDevice(&sensorRich);

  sensorGery.addProperty(&doorOpenGery);
  adapter->addDevice(&sensorGery);

  relayRich.addProperty(&closeDoorRich);
  adapter->addDevice(&relayRich);

  relayGery.addProperty(&closeDoorGery);
  adapter->addDevice(&relayGery);
  
  adapter->begin();
  
  Serial.println("HTTP server started");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/things/");
  Serial.print(sensorRich.id);
  Serial.print(" | ");
  Serial.print(sensorGery.id);
  Serial.print(" | ");
  Serial.print(relayRich.id);
  Serial.print(" | ");
  Serial.print(relayGery.id);
}

int previousDoorValueRich = 0;
bool lastOnRich = false;
int previousDoorValueGery = 0;
bool lastOnGery = false;
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    initWifi();
    initAdapter();
  }
  
  int doorValueRich = digitalRead(doorSensorPinRich);
  if (previousDoorValueRich != doorValueRich) {
    Serial.print("New door value: ");
    Serial.println(doorValueRich);
    previousDoorValueRich = doorValueRich;

    ThingPropertyValue thingValueRich;
    thingValueRich.boolean = !doorValueRich;
    doorOpenRich.setValue(thingValueRich);
  }

  int doorValueGery = digitalRead(doorSensorPinGery);
  if (previousDoorValueGery != doorValueGery) {
    Serial.print("New door value: ");
    Serial.println(doorValueGery);
    previousDoorValueGery = doorValueGery;

    ThingPropertyValue thingValueGery;
    thingValueGery.boolean = !doorValueGery;
    doorOpenGery.setValue(thingValueGery);
  }
  adapter->update();

  bool onRich = closeDoorRich.getValue().boolean;
  if (lastOnRich != onRich) {
    Serial.println("Turning On");
    digitalWrite(relayPinRich, HIGH);
    delay(500);
    digitalWrite(relayPinRich, LOW);
  }
  lastOnRich = onRich;

  bool onGery = closeDoorGery.getValue().boolean;
  if (lastOnGery != onGery) {
    Serial.println("Turning On");
    digitalWrite(relayPinGery, HIGH);
    delay(500);
    digitalWrite(relayPinGery, LOW);
  }
  lastOnGery = onGery;
}
