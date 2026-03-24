#include "LCD_module.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void initI2C() {
    Wire.begin(I2C_SDA, I2C_SCL); // Initialize I2C before LCD
    Serial.println("I2C LCD successfully connected.");
    lcd.init();
    lcd.backlight();
    lcd.clear();
}