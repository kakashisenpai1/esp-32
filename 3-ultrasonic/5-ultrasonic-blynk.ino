#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define trigPin 18 //D18
#define echoPin 19 //D19

char auth[] = "QLUXgILj0-8XPlKjDGOnvP3Fkdb4kdjH";
char ssid[] = "Yo";
char pass[] = "ramzhots123";

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(115200);

  // Menghubungkan ke Wi-Fi
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration*0.034/2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  Blynk.virtualWrite(V1, distance);
  
  delay(1000);
}




