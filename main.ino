#include <LiquidCrystal.h>

const int tempPin = A0;
const int ledPin = 8;
const int buzzerPin = 9;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("System Start");
  delay(1000);
  lcd.clear();
}

void loop() {
  int sensorValue = analogRead(tempPin);

  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  String statusText;

  if (temperature < 25) {
    statusText = "Normal";
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  } else if (temperature <= 30) {
    statusText = "Warm";
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, LOW);
  } else {
    statusText = "DANGER";
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);

  lcd.setCursor(0, 1);
  lcd.print(statusText);

  delay(1000);
}
