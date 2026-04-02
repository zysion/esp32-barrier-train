#include "alert_module.h"

TaskHandle_t alertTaskHandle = NULL;

void initAlert() {
    pinMode(ALERT_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void alertTask(void *parameter) {
    
    bool ledState = false;
    int currentState = UNKNOWN;  

    while (true) {
        if (isopenbarrier) {
            if (currentState != SAFE) {
                lcd.clear();
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(ALERT_LED_PIN, LOW);
                sendalertstatus_SAFE();
                currentState = SAFE;
            }
            vTaskDelay(100 / portTICK_PERIOD_MS);
            continue;
        }

        if (distance < 5.0f && distance >= 0.0f) {
            if (currentState != ALERT) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("NGUY HIEM");
                lcd.setCursor(0, 1);
                lcd.print("LUI LAI");
                vTaskDelay(200 / portTICK_PERIOD_MS); // Short delay to ensure LCD updates before buzzer
                currentState = ALERT;
                digitalWrite(BUZZER_PIN, HIGH);

                // Send DANGER alert via webserver
                sendalertstatus_DANGER();
            }
            ledState = !ledState;
            digitalWrite(ALERT_LED_PIN, ledState ? HIGH : LOW);
            vTaskDelay(125 / portTICK_PERIOD_MS);
        } else if (distance > 5.0f && distance < 10.0f) {
            if (currentState != DANGER) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("NGUY HIEM");
                lcd.setCursor(0, 1);
                lcd.print("DUNG LAI");
                vTaskDelay(200 / portTICK_PERIOD_MS); // Short delay to ensure LCD updates before buzzer
                currentState = DANGER;
                digitalWrite(BUZZER_PIN, LOW);
                // Send DANGER alert via webserver
                sendalertstatus_DANGER();
            }
            ledState = !ledState;
            digitalWrite(ALERT_LED_PIN, ledState ? HIGH : LOW);
            vTaskDelay(250 / portTICK_PERIOD_MS);
        } else {
            if (currentState != SAFE) {
                lcd.clear();
                currentState = SAFE;
                // Send SAFE alert via webserver
                sendalertstatus_SAFE();
            }
            digitalWrite(BUZZER_PIN, LOW);
            digitalWrite(ALERT_LED_PIN, LOW);
            ledState = false;
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
}