#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include <global.h>

#define I2C_SDA 19
#define I2C_SCL 20

extern LiquidCrystal_I2C lcd;

void initI2C();

#endif // LCD_MODULE_H