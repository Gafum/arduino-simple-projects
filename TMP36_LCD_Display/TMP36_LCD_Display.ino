int TMP36 = A0;
int sensorValue;
int temperature = 0;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(TMP36);

  temperature = map(sensorValue, 0, 410, -50, 150);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");
  Serial.print(temperature);
  Serial.println(" C");

  delay(500);
}
