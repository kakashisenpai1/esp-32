#define BLYNK_PRINT Serial

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "QLUXgILj0-8XPlKjDGOnvP3Fkdb4kdjH";
char ssid[] = "Yo";
char pass[] = "ramzhots123";

// Define the SDA and SCL pins for your board
#define SDA 21
#define SCL 22

// Define buzzer pin number
#define BUZZER_PIN 12

// Set up the LCD object with the I2C address and size
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

void setup()
{
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);

  // Menghubungkan ke Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the I2C bus with the SDA and SCL pins
  Wire.begin(SDA, SCL);

  // Initialize the LCD object
  lcd.begin();
  lcd.backlight();

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1) {
  int buzzerStatus = param.asInt();

  Serial.println(buzzerStatus);
  lcd.clear();

  if (buzzerStatus == 300) {
    Serial.println("On");
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("ON");
  } else {
    Serial.println("Off");
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(0, 0);
    lcd.print("OFF");
  }
}





