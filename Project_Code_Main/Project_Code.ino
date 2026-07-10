///////////////////////////////////////////////////////
//          GAS + FIRE SYSTEM WITH REMOTEXY         //
///////////////////////////////////////////////////////

//----------------------------------------------------
//                 REMOTEXY MODE
//----------------------------------------------------

#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

//----------------------------------------------------
//                    LIBRARIES
//----------------------------------------------------

#include <RemoteXY.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//----------------------------------------------------
//              REMOTEXY SETTINGS
//----------------------------------------------------

#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600

#define REMOTEXY_WIFI_SSID "Arduino"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

//----------------------------------------------------
//               REMOTEXY CONFIG
//----------------------------------------------------

#pragma pack(push, 1)

uint8_t RemoteXY_CONF[] = {

  255,1,0,7,0,66,0,19,0,0,0,0,31,1,106,200,1,1,5,0,
  2,41,22,25,16,0,40,26,31,31,79,78,0,79,70,70,0,
  67,17,59,73,9,78,40,26,2,
  70,44,95,17,17,16,31,1,0,
  70,44,119,17,17,16,31,204,0,
  70,44,143,17,17,16,31,19,0

};

struct {

  uint8_t Gas_switch_02;
  float Gas_Value;

  uint8_t Gas_led_Red;
  uint8_t Gas_led_Blue;
  uint8_t Gas_led_yellow;

  uint8_t connect_flag;

} RemoteXY;

#pragma pack(pop)

///////////////////////////////////////////////////////
//                  HARDWARE PINS
///////////////////////////////////////////////////////

#define flamePin   2
#define gasPin     A0

#define buzzer     8

#define yellowLED  13
#define blueLED    12
#define redLED     11

#define fanPin     7
#define servoPin   6

///////////////////////////////////////////////////////
//                    OBJECTS
///////////////////////////////////////////////////////

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

///////////////////////////////////////////////////////
//                  GAS LEVELS
///////////////////////////////////////////////////////

int yellowLevel = 450;
int blueLevel   = 550;
int redLevel    = 650;

///////////////////////////////////////////////////////
//                   VARIABLES
///////////////////////////////////////////////////////

bool servoState = false;

unsigned long buzzerTimer = 0;
bool buzzerState = false;

///////////////////////////////////////////////////////
//                     SETUP
///////////////////////////////////////////////////////

void setup() {

  // SERIAL START
  Serial.begin(9600);

  // REMOTEXY START
  RemoteXY_Init();

  // PIN MODES
  pinMode(flamePin, INPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(fanPin, OUTPUT);

  // SERVO
  myServo.attach(servoPin);
  myServo.write(0);

  // LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Smart System");

  delay(1500);

  lcd.clear();
}

///////////////////////////////////////////////////////
//                      LOOP
///////////////////////////////////////////////////////

void loop() {

  // IMPORTANT
  RemoteXY_Handler();

  //--------------------------------------------------
  // SENSOR READ
  //--------------------------------------------------

  int flame = digitalRead(flamePin);
  int gas = analogRead(gasPin);

  RemoteXY.Gas_Value = gas;

  //--------------------------------------------------
  // SERVO AUTO CONTROL
  //--------------------------------------------------

  if (flame == LOW || gas >= yellowLevel) {

    servoState = true;

  } else {

    servoState = false;
  }

  if (servoState) {

    myServo.write(180);

    // STATUS ON
    RemoteXY.Gas_switch_02 = 0;

  } else {

    myServo.write(0);

    // STATUS OFF
    RemoteXY.Gas_switch_02 = 1;
  }

  //--------------------------------------------------
  // LCD DISPLAY
  //--------------------------------------------------

  lcd.setCursor(0,0);

  if (flame == LOW) {

    lcd.print("FIRE DETECTED ");

  }
  else if (gas >= redLevel) {

    lcd.print("STATUS:DANGER ");

  }
  else if (gas >= blueLevel) {

    lcd.print("STATUS:HIGH   ");

  }
  else if (gas >= yellowLevel) {

    lcd.print("STATUS:WARNING");

  }
  else {

    lcd.print("STATUS:SAFE   ");
  }

  lcd.setCursor(0,1);

  lcd.print("GAS:");
  lcd.print(gas);
  lcd.print("    ");

  //--------------------------------------------------
  // RESET LEDS
  //--------------------------------------------------

  digitalWrite(yellowLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);

  //--------------------------------------------------
  // FIRE DETECTED
  //--------------------------------------------------

  if (flame == LOW) {

    digitalWrite(redLED, HIGH);

    digitalWrite(fanPin, HIGH);

    RemoteXY.Gas_led_Red = 1;
    RemoteXY.Gas_led_Blue = 0;
    RemoteXY.Gas_led_yellow = 0;

    buzzerBlink(120);
  }

  //--------------------------------------------------
  // RED LEVEL
  //--------------------------------------------------

  else if (gas >= redLevel) {

    digitalWrite(yellowLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, HIGH);

    digitalWrite(fanPin, HIGH);

    RemoteXY.Gas_led_Red = 1;
    RemoteXY.Gas_led_Blue = 1;
    RemoteXY.Gas_led_yellow = 1;

    buzzerBlink(100);
  }

  //--------------------------------------------------
  // BLUE LEVEL
  //--------------------------------------------------

  else if (gas >= blueLevel) {

    digitalWrite(yellowLED, HIGH);
    digitalWrite(blueLED, HIGH);

    digitalWrite(fanPin, HIGH);

    RemoteXY.Gas_led_Red = 0;
    RemoteXY.Gas_led_Blue = 1;
    RemoteXY.Gas_led_yellow = 1;

    buzzerBlink(200);
  }

  //--------------------------------------------------
  // YELLOW LEVEL
  //--------------------------------------------------

  else if (gas >= yellowLevel) {

    digitalWrite(yellowLED, HIGH);

    digitalWrite(fanPin, HIGH);

    RemoteXY.Gas_led_Red = 0;
    RemoteXY.Gas_led_Blue = 0;
    RemoteXY.Gas_led_yellow = 1;

    buzzerBlink(350);
  }

  //--------------------------------------------------
  // SAFE MODE
  //--------------------------------------------------

  else {

    digitalWrite(fanPin, LOW);

    digitalWrite(buzzer, LOW);

    RemoteXY.Gas_led_Red = 0;
    RemoteXY.Gas_led_Blue = 0;
    RemoteXY.Gas_led_yellow = 0;
  }

  delay(10);
}

///////////////////////////////////////////////////////
//               BUZZER FUNCTION
///////////////////////////////////////////////////////

void buzzerBlink(unsigned long interval) {

  unsigned long currentMillis = millis();

  if (currentMillis - buzzerTimer >= interval) {

    buzzerTimer = currentMillis;

    buzzerState = !buzzerState;

    digitalWrite(buzzer, buzzerState);
  }
}