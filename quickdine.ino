#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// HX711 pins for one chair
#define DT1  32
#define SCK1 33

HX711 scale1;

// LCD I2C address (adjust if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Threshold: You can calibrate and update this value later
const long OCCUPIED_THRESHOLD = 50000;

void setup() {
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Quick Dine Init");
  delay(2000);
  lcd.clear();

  // Initialize HX711
  scale1.begin(DT1, SCK1);
  scale1.tare();  // Zero the scale

  Serial.println("Taring done. System ready.");
}

void loop() {
  long w1 = scale1.is_ready() ? scale1.read_average() : 0;

  // Print raw value for calibration help
  Serial.print("Raw Weight: ");
  Serial.println(w1);

  // Determine occupancy
  bool isOccupied = (w1 > OCCUPIED_THRESHOLD);

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chair 1: ");
  lcd.print(isOccupied ? "Occupied" : "Free");

  delay(1000);
}