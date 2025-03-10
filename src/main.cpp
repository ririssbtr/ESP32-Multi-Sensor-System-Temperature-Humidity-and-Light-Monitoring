#include <Arduino.h>
// Rumiris Butarbutar
// 233140707111130
// LCD I2C dengan sensor suhu

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHTesp.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

const int DHT_PIN = 13;  // Pin sensor DHT-22
const int LDR_PIN = 34;  // Pin sensor LDR

DHTesp dhtSensor;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);  
  lcd.init();
  lcd.backlight();
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  int ldrValue = analogRead(LDR_PIN);  
  float lightIntensity = map(ldrValue, 0, 4095, 0, 100);  // Konversi ke %

  lcd.clear();

  lcd.setCursor(0, 0); 
  lcd.print("Tampilan Sensor Suhu");
    
  lcd.setCursor(3, 1); 
  lcd.print("Suhu : " + String(data.temperature, 2) + " C");
  
  lcd.setCursor(1, 2);
  lcd.print("Kelembapan: " + String(data.humidity, 2) + "%");

  lcd.setCursor(3, 3);
  lcd.print("Cahaya: " + String(lightIntensity, 2) + "%");

  delay(2000);  // Delay selama 2 detik
}
