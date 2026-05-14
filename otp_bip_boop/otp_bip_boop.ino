/*************************************************************
   ESP32 + Blynk.Edgent
   Reprise de ton sketch avec provisioning WiFi dynamique
 *************************************************************/

// Required by blynk
#define BLYNK_TEMPLATE_ID           "TMPL57cB3JhFw"
#define BLYNK_TEMPLATE_NAME         "gyro2"
#define BLYNK_FIRMWARE_VERSION      "1.0.4"

#define BLYNK_PRINT Serial
#define APP_DEBUG

#include <WiFi.h>
#include "BlynkEdgent.h"

// --- BLYNK PINs ---
#define OTA_BUTTON V2
#define PLAY1_BUTTON V1
#define PLAY2_BUTTON V3
#define PLAY3_BUTTON V4

BlynkTimer timer;

// Broches
const int buzzerPin = 1;
const int relayPin  = 8;

// Tonalités et durée
const int tone1 = 1000;
const int tone2 = 1500;
const int toneDuration = 150;

// --------------------------------------------------
// Helpers
// --------------------------------------------------
void small_blink() {
  digitalWrite(relayPin, HIGH);
  delay(250);
  digitalWrite(relayPin, LOW);
  delay(250);
}

void big_blink() {
  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  delay(500);
}

void playTone(int freq, int durationMs, int pauseMs = 20) {
  tone(buzzerPin, freq);
  delay(durationMs);
  noTone(buzzerPin);
  delay(pauseMs);
}

// --------------------------------------------------
// Blynk handlers
// --------------------------------------------------
BLYNK_CONNECTED() {
  Blynk.virtualWrite(OTA_BUTTON, 0);
  Blynk.virtualWrite(PLAY1_BUTTON, 0);
  Blynk.virtualWrite(PLAY2_BUTTON, 0);
  Blynk.virtualWrite(PLAY3_BUTTON, 0);
}

// Mcdo
BLYNK_WRITE(PLAY1_BUTTON) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relayPin, HIGH);

    playTone(tone2, toneDuration, 15);
    playTone(tone1, toneDuration, 15);
    playTone(tone2, toneDuration, 15);
    playTone(tone1, toneDuration, 15);
    playTone(tone2, toneDuration, 25);

    digitalWrite(relayPin, LOW);
    Blynk.virtualWrite(PLAY1_BUTTON, 0);
  }
}

// Music
BLYNK_WRITE(PLAY2_BUTTON) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relayPin, HIGH);

    playTone(262, 200, 30); // do
    playTone(294, 200, 30); // ré
    playTone(330, 200, 30); // mi
    playTone(294, 200, 30); // ré
    playTone(262, 200, 30); // do
    playTone(330, 200, 30); // mi
    playTone(392, 400, 30); // sol

    digitalWrite(relayPin, LOW);
    Blynk.virtualWrite(PLAY2_BUTTON, 0);
  }
}

// Urgences
BLYNK_WRITE(PLAY3_BUTTON) {
  int state = param.asInt();

  if (state == 1) {
    digitalWrite(relayPin, HIGH);

    playTone(435, 600, 20);  // Ton grave
    playTone(580, 600, 20);  // Ton aigu
    playTone(435, 600, 20);  // Ton grave
    playTone(580, 600, 20);  // Ton aigu
    playTone(435, 600, 20);  // Ton grave
    playTone(580, 600, 20);  // Ton aigu

    digitalWrite(relayPin, LOW);
    Blynk.virtualWrite(PLAY3_BUTTON, 0);
  }
}

// Bouton OTA dans Blynk
// Avec Edgent, l'OTA est normalement géré par Blynk.Air.
// Ici on garde un bouton pour déclencher une synchro/trace locale.
BLYNK_WRITE(OTA_BUTTON) {
  int pinValue = param.asInt();

  if (pinValue == 1) {
    Serial.println("OTA button pressed from Blynk");
    small_blink();

    // Ici, pas de httpUpdate GitHub :
    // les updates se font via Blynk.Edgent / Blynk.Air
    // quand tu déploies un firmware depuis Blynk.Console.

    Blynk.virtualWrite(OTA_BUTTON, 0);
  }
}

// --------------------------------------------------
// Setup / Loop
// --------------------------------------------------
void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

  Serial.begin(115200);
  delay(100);

  big_blink();

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}