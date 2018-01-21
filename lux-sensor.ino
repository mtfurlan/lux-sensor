#include <stdio.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <BH1750.h>
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))



U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R3, /* reset=*/ U8X8_PIN_NONE);
BH1750 lightMeter(0x23);


unsigned long status = 0UL;
unsigned long statusInterval = 300UL;

char buf[128];

void display() {
  int light = lightMeter.readLightLevel();
  Serial.println(light);
  itoa(light, buf, 10);
  u8g2.clearBuffer();
  u8g2.drawStr(0, 50, buf);
  u8g2.sendBuffer();
}


void setup() {
  Serial.begin(115200);

  u8g2.begin();
  u8g2.setFont(u8g2_font_inr16_mn);
  Serial.println("Display started?");

  lightMeter.begin(BH1750_CONTINUOUS_HIGH_RES_MODE);
}


void loop() {
  if( (long)( millis() - status ) >= 0) {
    status = millis() + statusInterval;
    Serial.println("display");
    display();
  }
}
