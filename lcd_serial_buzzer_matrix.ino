/*
  lcd_serial_buzzer_matrix.ino
  Arduino Uno R3 + 16x2 LCD + Active Buzzer + MAX7219 LED Matrix
  Receives serial messages from Python (OpenCV gestures)
  "HI" -> LCD shows "Hi" + short beep + matrix shows hand icon
  "NUM:n" -> LCD shows number n + n beeps + matrix shows digit n
*/

#include <LiquidCrystal.h>
#include <LedControl.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Buzzer pin
const int buzzerPin = 8;

// MAX7219: DIN, CLK, CS
LedControl lc = LedControl(7, 6, 9, 1);  // (DIN=7, CLK=6, CS=9, # of devices=1)

String inputString = "";
bool newMessage = false;

// Simple 8x8 hand icon
byte handIcon[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10111101,
  B10111101,
  B10011001,
  B01000010,
  B00111100
};

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  // Setup LED matrix
  lc.shutdown(0, false);   // Wake up
  lc.setIntensity(0, 8);   // Brightness (0–15)
  lc.clearDisplay(0);

  lcd.clear();
  lcd.print("Waiting...");
}

void loop() {
  // Read serial input
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      newMessage = true;
      break;
    } else {
      inputString += c;
    }
  }

  if (newMessage) {
    lcd.clear();
    lc.clearDisplay(0);

    if (inputString == "HI") {
      // LCD
      lcd.setCursor(0, 0);
      lcd.print("Hi!");

      // Buzzer
      tone(buzzerPin, 1000);
      delay(200);
      noTone(buzzerPin);

      // Matrix: draw hand
      for (int row = 0; row < 8; row++) {
        lc.setRow(0, row, handIcon[row]);
      }
    }
    else if (inputString.startsWith("NUM:")) {
      int num = inputString.substring(4).toInt();

      // LCD
      lcd.setCursor(0, 0);
      lcd.print("Number:");
      lcd.setCursor(0, 1);
      lcd.print(num);

      // Buzzer: beep num times
      for (int i = 0; i < num; i++) {
        tone(buzzerPin, 800);
        delay(150);
        noTone(buzzerPin);
        delay(150);
      }

      // Matrix: display digit (0–9)
      lc.setChar(0, 0, (char)('0' + num), false);
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("Unknown:");
      lcd.setCursor(0, 1);
      lcd.print(inputString);
    }

    inputString = "";
    newMessage = false;
  }
}
