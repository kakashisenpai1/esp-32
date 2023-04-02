#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

const int EN1 = 34;   // pin EN1 pada driver L293D
const int IN1 = 32;   // pin IN1 pada driver L293D
const int IN2 = 25;   // pin IN2 pada driver L293D

const int PB0 = 13;

const int PWM_FREQ = 5000;  // frekuensi PWM (Hz)

char auth[] = "QLUXgILj0-8XPlKjDGOnvP3Fkdb4kdjH";
char ssid[] = "Yo";
char pass[] = "ramzhots123";

void setup() {
  // set pin mode
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(PB0, INPUT_PULLUP);

  // set LEDC timer dan channel untuk menghasilkan sinyal PWM pada pin EN1
  ledcSetup(0, PWM_FREQ, 8);
  ledcAttachPin(EN1, 0);

  // Menghubungkan ke Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected!");

  Blynk.begin(auth, ssid, pass);

  Serial.begin(9600);
}

void loop() {
  int pb0state = digitalRead(PB0);

  if (pb0state == LOW) {
    ledcWrite(0, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    Blynk.virtualWrite(V1, 1);
  } else {
    ledcWrite(0, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    Blynk.virtualWrite(V1, 0);
  }
}



