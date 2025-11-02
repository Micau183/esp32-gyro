/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_NAME "gyro2"
#define BLYNK_AUTH_TOKEN "Rksk7itSJdxVW9m9vmaHtAgv49j_DygK"
#define BLYNK_TEMPLATE_ID "TMPL57cB3JhFw"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Freebox-6D4814";
char pass[] = "felicula.!-conbina7!-vestigant?-opposui";

// Broche du buzzer
const int buzzerPin = 1;

const int relayPin = 8;

// Tonalités et durée
const int tone1 = 1000;      // Hz
const int tone2 = 1500;      // Hz
const int toneDuration = 150; // ms

BLYNK_WRITE(V1) { // Bouton sur le Virtual Pin V1
  int state = param.asInt();

  if (state == 1) { // Bouton activé

    digitalWrite(relayPin, HIGH);

    tone(buzzerPin, tone2);
    delay(toneDuration);
    noTone(buzzerPin);
    delay(15);

    tone(buzzerPin, tone1);
    delay(toneDuration);
    noTone(buzzerPin);
    delay(15);

    tone(buzzerPin, tone2);
    delay(toneDuration);
    noTone(buzzerPin);
    delay(15);

    tone(buzzerPin, tone1);
    delay(toneDuration);
    noTone(buzzerPin);
    delay(15);

    tone(buzzerPin, tone2);
    delay(toneDuration);
    noTone(buzzerPin);
    delay(25);

    digitalWrite(relayPin, LOW);



    // Remet le bouton à OFF pour pouvoir rejouer
    Blynk.virtualWrite(V1, 0);
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
