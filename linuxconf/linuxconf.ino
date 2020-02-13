#include <Arduino.h>
#include "Thing.h"
#include "WebThingAdapter.h"
#include <WiFi.h>

#include "config.h"

const int ledPin = 15;
WebThingAdapter* adapter;

const char* ledTypes[] = {"OnOffSwitch", "Light", nullptr};
ThingDevice led("led", "Warning light", ledTypes);
ThingProperty ledOn("on", "", BOOLEAN, "OnOffProperty");

void setup(void){
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
    
    initWifi();
    initAdapter();
}

void initWifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Retry in 5 secs");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(5000);
    }
    Serial.println("Connected");
}

void initAdapter() {
    adapter = new WebThingAdapter("light", WiFi.localIP());
    
    led.addProperty(&ledOn);
    adapter->addDevice(&led);
    
    adapter->begin();
    
    Serial.println("HTTP server started");
    Serial.print("http://");
    Serial.print(WiFi.localIP());
    Serial.print("/things/");
    Serial.print(led.id);
}

void loop(void) {
    adapter->update();
    bool on = ledOn.getValue().boolean;
    digitalWrite(ledPin, on ? HIGH : LOW);
}