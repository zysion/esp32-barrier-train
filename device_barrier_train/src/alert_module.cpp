#include "alert_module.h"

void initAlert() {
    pinMode(ALERT_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void alertTask(void *parameter) {
    
    bool ledState = false;
    int currentState = UNKNOWN;  

    while (true) {
        if (distance < 5.0f) {
            if (currentState != ALERT) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("NGUY HIEM");
                lcd.setCursor(0, 1);
                lcd.print("LUI LAI");
                currentState = ALERT;
                digitalWrite(BUZZER_PIN, HIGH);
            }
            ledState = !ledState;
            digitalWrite(ALERT_LED_PIN, ledState ? HIGH : LOW);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        } else if (distance > 5.0f && distance < 10.0f) {
            if (currentState != DANGER) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("NGUY HIEM");
                lcd.setCursor(0, 1);
                lcd.print("DUNG LAI");
                currentState = DANGER;
                digitalWrite(BUZZER_PIN, LOW);
            }
            ledState = !ledState;
            digitalWrite(ALERT_LED_PIN, ledState ? HIGH : LOW);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        } else {
            if (currentState != SAFE) {
                lcd.clear();
                currentState = SAFE;
            }
            digitalWrite(BUZZER_PIN, LOW);
            digitalWrite(ALERT_LED_PIN, LOW);
            ledState = false;
        }
    }
}