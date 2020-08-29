#include <LiquidCrystal.h>
#include <DHT.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT dht(7, DHT11);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  delay(500);
}

void loop() {
  lcd.noDisplay();
  delay(500);
  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T ");
  const float temperature = dht.readTemperature();
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("H ");
  const float humidity = dht.readHumidity();
  lcd.print(humidity);
  lcd.print(" %");
  delay(1000);
}
