#include "LCD_module.h"

void initI2C() {
    if (Wire.begin(I2C_SDA,I2C_SCL)) {
        Serial.println("I2C LCD successfully connected.");
    }

    LiquidCrystal_I2C lcd(0x27,16,2);

    lcd.init();
    lcd.backlight();
}