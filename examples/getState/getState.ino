#include <Wire.h>
#include <RobotClass_Gauge.h>

#ifdef CONFIG_IDF_TARGET_ESP32S3
#define I2C_SDA 3
#define I2C_SCL 8
#endif

RobotClass_Gauge gauge;

uint16_t pos = 0;
uint8_t btn = 0;

void setup() {
    Serial.begin(9600);
    delay(2000);

    #ifdef CONFIG_IDF_TARGET_ESP32S3
    gauge.begin(I2C_SDA, I2C_SCL);
    #else
    gauge.begin();
    #endif

    Serial.println("ready");

    gauge.setMode(MODE_POINT);
    gauge.test();
    delay(3000);

    uint8_t v = gauge.getVersion();
    Serial.print("version=");
    Serial.println(v);
}

void loop() {
    gauge.getState(&pos, &btn); 
    Serial.print("count=");
    Serial.print(pos);
    Serial.print(", btn=");
    Serial.println(btn);
    delay(100);
}