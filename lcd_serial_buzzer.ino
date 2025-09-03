/*
  lcd_serial_buzzer.ino
  Arduino Uno R3 + 16x2 LCD + Active Buzzer
  Receives serial messages from Python (OpenCV gestures)
  "HI" -> display "Hi" + short beep
  "NUM:n" -> display number n + beep n times
*/

#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7 (adjust if wired differently)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Buzzer pin (digital)
const int buzzerPin = 8;

String inputString = "";   // Incoming serial message
bool newMessage = false;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);

  lcd.clear();
  lcd.print("Waiting...");
}

void loop() {
  // Read incoming serial
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      newMessage = true;
      break;
    } else {
      inputString += c;
    }
  }

  // Process new message
  if (newMessage) {
    lcd.clear();

    if (inputString == "HI") {
      lcd.setCursor(0, 0);
      lcd.print("Hi!");

      // Short beep
      tone(buzzerPin, 1000); // 1 kHz tone
      delay(200);
      noTone(buzzerPin);
    }
    else if (inputString.startsWith("NUM:")) {
      int num = inputString.substring(4).toInt();
      lcd.setCursor(0, 0);
      lcd.print("Number:");
      lcd.setCursor(0, 1);
      lcd.print(num);

      // Beep num times
      for (int i = 0; i < num; i++) {
        tone(buzzerPin, 800); // 800 Hz tone
        delay(150);
        noTone(buzzerPin);
        delay(150);
      }
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("Unknown:");
      lcd.setCursor(0, 1);
      lcd.print(inputString);
    }

    // Reset for next message
    inputString = "";
    newMessage = false;
  }
}
