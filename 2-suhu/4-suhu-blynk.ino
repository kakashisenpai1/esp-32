// For debugging
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "QLUXgILj0-8XPlKjDGOnvP3Fkdb4kdjH";
char ssid[] = "Yo";
char pass[] = "ramzhots123";

#define DHTPIN 4          // pin data sensor DHT11 terhubung ke GPIO 4
#define DHTTYPE DHT11     // jenis sensor DHT yang digunakan

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);   // koneksi ke jaringan WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Gagal terhubung ke jaringan WiFi...");
  }
  Serial.println("Terhubung ke jaringan WiFi");

  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop()
{
  Blynk.run();
  float h = dht.readHumidity();       // baca kelembaban dari sensor DHT
  float t = dht.readTemperature();    // baca suhu dari sensor DHT

  Serial.println(h);
  Serial.println(t);

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca data dari sensor DHT11!");
    return;
  }

  Blynk.virtualWrite(V1, t);   // kirim data suhu ke Blynk pada pin virtual V1
  Blynk.virtualWrite(V2, h);   // kirim data kelembaban ke Blynk pada pin virtual V2
  delay(2000);
}






