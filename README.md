# Smart Temperature Monitoring System

## Author
Khaled Mohamed

---

## Project Description

This project is a smart temperature monitoring system built using Arduino.  
It reads temperature data from a sensor and reacts using visual and sound alerts.  
The system also displays real-time information on an LCD and sends data through serial communication.

---

## Features

- Temperature measurement using TMP36 sensor
- LED indicator for system status
- Buzzer alarm for high temperature
- LCD display (16x2) for real-time output
- Serial communication for monitoring data
- Multi-level warning system

---

## System Behavior

| Temperature Range | Status  | LED  | Buzzer |
|------------------|--------|------|--------|
| Below 25°C       | Normal | OFF  | OFF    |
| 25°C – 30°C      | Warm   | ON   | OFF    |
| Above 30°C       | Danger | ON   | ON     |

---

## Components Used

- Arduino Uno
- TMP36 Temperature Sensor
- LED
- Buzzer
- 16x2 LCD Display
- Potentiometer (10kΩ)
- Resistors (220Ω)
- Jumper wires

---

## Circuit Description

- TMP36 sensor connected to A0
- LED connected to digital pin 8 (with resistor)
- Buzzer connected to digital pin 9
- LCD connected in 4-bit mode
- Potentiometer used to control LCD contrast

---

## Arduino Code

```cpp
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
  } 
  else if (temperature <= 30) {
    statusText = "Warm";
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, LOW);
  } 
  else {
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

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C | Status: ");
  Serial.println(statusText);

  delay(1000);
}
