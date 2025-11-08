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

#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Freebox-6D4814";
char pass[] = "felicula.!-conbina7!-vestigant?-opposui";


const char* firmware_url = "https://raw.githubusercontent.com/Micau183/esp32-gyro/gh-pages/ESP32_WiFi.ino.bin";

const char* version_url  = "https://micau183.github.io/esp32-gyro/ESP32_WiFi/version.txt";

String currentVersion = "1.0";

// --- BLYNK PIN pour le bouton ---
#define OTA_BUTTON V2  // bouton dans l'app Blynk

BlynkTimer timer;


// Broche du buzzer
const int buzzerPin = 1;

const int relayPin = 8;

// Tonalités et durée
const int tone1 = 1000;      // Hz
const int tone2 = 1500;      // Hz
const int toneDuration = 450; // ms

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

BLYNK_WRITE(V3) { // Bouton sur le Virtual Pin V3
  int state = param.asInt();

  if (state == 1) { // Bouton activé
    digitalWrite(relayPin, HIGH);

    // Exemple de mélodie : do ré mi ré do mi sol
    tone(buzzerPin, 262); // do
    delay(200);
    noTone(buzzerPin);
    delay(30);

    tone(buzzerPin, 294); // ré
    delay(200);
    noTone(buzzerPin);
    delay(30);

    tone(buzzerPin, 330); // mi
    delay(200);
    noTone(buzzerPin);
    delay(30);

    tone(buzzerPin, 294); // ré
    delay(200);
    noTone(buzzerPin);
    delay(30);

    tone(buzzerPin, 262); // do
    delay(200);
    noTone(buzzerPin);
    delay(30);

    tone(buzzerPin, 330); // mi
    delay(200);
    noTone(buzzerPin);
    delay(30);

    tone(buzzerPin, 392); // sol
    delay(400);
    noTone(buzzerPin);
    delay(30);

    digitalWrite(relayPin, LOW);

    // Remet le bouton à OFF pour pouvoir rejouer
    Blynk.virtualWrite(V3, 0);
  }
}
void small_blink(){

  digitalWrite(relayPin, HIGH);
  delay(250);
  digitalWrite(relayPin, LOW);
  delay(250);

}
void big_blink(){

  digitalWrite(relayPin, HIGH);
  delay(500);
  digitalWrite(relayPin, LOW);
  delay(500);

}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.virtualWrite(OTA_BUTTON, 0);
    // Activer le debug pour HTTPUpdate
  Serial.setDebugOutput(true);
  big_blink();
}

void loop() {
  Blynk.run();
}

// --- Fonction déclenchée par le bouton Blynk ---
BLYNK_WRITE(OTA_BUTTON) {
  int pinValue = param.asInt();
  if(pinValue == 1) { // bouton appuyé
    Serial.println("OTA triggered from Blynk!");
    small_blink();
    checkForUpdate();
    Serial.println("update ok");
    Blynk.virtualWrite(OTA_BUTTON, 0);
  }
}
void checkForUpdate() {
  Serial.println("Starting OTA update...");
  small_blink();

  WiFiClientSecure client;
  client.setInsecure(); // ok pour GitHub Pages

  // Appel OTA avec le même client
  t_httpUpdate_return ret = httpUpdate.update(client, firmware_url);

  switch(ret) {
    case HTTP_UPDATE_OK:
      big_blink();
      big_blink();
      Serial.println("Update successful! ESP will reboot.");
      ESP.restart();
      break;
    case HTTP_UPDATE_FAILED:
      small_blink();
      small_blink();
      small_blink();
      Serial.printf("Update failed (%d): %s\n",
                    httpUpdate.getLastError(),
                    httpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No update performed.");
      break;
  }
}

