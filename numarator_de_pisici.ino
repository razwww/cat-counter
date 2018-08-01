/*
  Copyright © 2018 Razvan Murariu <razwww@gmail.com>
  This program is free software. It comes without any warranty, to
  the extent permitted by applicable law. You can redistribute it
  and/or modify it under the terms of the Do What The Fuck You Want
  To Public License, Version 2, as published by Sam Hocevar. See
  the COPYING file for more details.

  The circuit:
  Arduino Nano
  trigPin: A1
  echoPin: A0
  display SCL: A4
  display SDA: A5
  button (NC): between 5V and GND&D2
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const long intervalEat = 120000;
const long intervalLight = 5000;
int distanta = 12;
long duration;
int distanceCm;
int numarator = 0;
int buttonState = 0;
unsigned long previousMillisEat = 0;
unsigned long previousMillisButton = 0;
const int trigPin = A1;
const int echoPin = A0;

void setup() {
  lcd.begin(16,2);
  
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(13, OUTPUT);
  pinMode(2, INPUT); // button for backlight
  
  lcd.setCursor(0,0);
  lcd.print("0   pisici");
  lcd.backlight();
  delay(intervalLight);
  lcd.noBacklight();
}

void loop() {
  unsigned long currentMillis = millis();

  delay(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  
  // distance smaller than 12 cm && (just powered on || intervalEat passed)
  if (distanceCm < distanta && ((currentMillis < intervalEat && numarator == 0) || (currentMillis - previousMillisEat >= intervalEat))) {
    previousMillisEat = currentMillis;
    numarator++;
    Serial.print(distanceCm);
    Serial.println(" cm");
    Serial.print(numarator);
    Serial.println(" pisici");
    Serial.println(currentMillis);
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(numarator);
    delay(intervalLight);
    lcd.noBacklight();
  }
  
  buttonState = digitalRead(2);
  if (buttonState == LOW) {
    Serial.println("Buton");    
    lcd.backlight();
    previousMillisButton = currentMillis;
    }
    
  if ( currentMillis - previousMillisButton >= intervalLight ) {
    lcd.noBacklight();
    }

}
