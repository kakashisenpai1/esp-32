#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Set up the Wi-Fi network to connect to
char ssid[] = "Yo";
char pass[] = "ramzhots123";

// Set up the Blynk authentication token
char auth[] = "QLUXgILj0-8XPlKjDGOnvP3Fkdb4kdjH";

// Set up the LED pin on the ESP32
int ledPin = 13; // IO13

void setup()
{
  Serial.begin(9600);

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Connect to the Blynk server
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    delay(1000);
    Serial.println("Connecting to Blynk server...");
  }

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  Serial.println("Connected to Wi-Fi and Blynk server");
}

void loop()
{
  Blynk.run();
}

// Function to turn on or off the LED based on the value of the virtual pin
BLYNK_WRITE(V1) {
  int pinValue = param.asInt(); // Get the value of the virtual pin

  if (pinValue == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
    Serial.println("LED turned on");
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED
    Serial.println("LED turned off");
  }
}



