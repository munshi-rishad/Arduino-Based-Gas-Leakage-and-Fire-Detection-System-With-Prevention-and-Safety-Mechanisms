#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define flamePin 2
#define gasPin   3
#define buzzer   8
#define ledPin   13

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  pinMode(flamePin, INPUT_PULLUP);
  pinMode(gasPin,   INPUT_PULLUP);   // <-- makes signal stable
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  }

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 12);
  oled.print("Fire & Gas System");
  oled.display();
  delay(1000);
}

void loop() {

  int flame = digitalRead(flamePin);
  int gas   = digitalRead(gasPin);

  // Debug to Serial
  Serial.print("Flame=");
  Serial.print(flame);
  Serial.print("  Gas=");
  Serial.println(gas);

  oled.clearDisplay();
  oled.setTextSize(1);

  // NOTE: Because of INPUT_PULLUP
  // 1 = DETECTED, 0 = SAFE
  oled.setCursor(0, 12);
  oled.print("Flame: ");
  oled.print(flame == HIGH ? "DETECTED" : "SAFE");

  oled.setCursor(0, 28);
  oled.print("Gas:   ");
  oled.print(gas == HIGH ? "DETECTED" : "SAFE");

  oled.setCursor(0, 46);
  if (flame == HIGH || gas == HIGH)
    oled.print("STATUS: DANGER !!!");
  else
    oled.print("STATUS: NORMAL");

  oled.display();

  if (flame == HIGH || gas == HIGH) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(120);
}
