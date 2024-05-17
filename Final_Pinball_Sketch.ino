#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

int vib_pins[] = {8, 7, 6}; // Pins for vibration sensors
int motion_pin = 5; // Pin for motion sensor
int score = 0; // Initialize score variable

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

int pos = 0;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(vib_pins[i], INPUT);
  }
  pinMode(motion_pin, INPUT);

  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  myServo.attach(9);
  myServo.write(0);
  delay(1000);
}

void loop() {
  // Check vibration sensors
  for (int i = 0; i < 3; i++) {
    if (digitalRead(vib_pins[i]) == HIGH) {
      score += 10;
      delay(2000); // Delay to prevent multiple increments from a single vibration
    }
  }

  // Check motion sensor
  if (digitalRead(motion_pin) == LOW) {
    score += 20;
    delay(2000); // Delay to prevent multiple increments from continuous motion
  }

  // Control servo
  if (pos < 180) {
    myServo.write(pos);
    pos += 10;
    delay(100); // Decreased delay for faster movement
  } else {
    myServo.write(pos);
    pos = 0;
  }

  // Display score on LCD and Serial monitor
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(score);

  Serial.print("Score: ");
  Serial.println(score);

  delay(1000); // Delay to avoid flickering display
}