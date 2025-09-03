/*
  lcd_serial.ino
  Arduino Uno R3 + 16x2 LCD
  Receives serial messages from Python (OpenCV gestures)
  "HI" -> display "Hi"
  "NUM:n" -> display number n (future extension)
*/

#include <LiquidCrystal.h>

// Pins: RS, E, D4, D5, D6, D7 (adjust if wired differently)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String inputString = "";   // Incoming serial message
bool newMessage = false;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

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
    }
    else if (inputString.startsWith("NUM:")) {
      int num = inputString.substring(4).toInt();
      lcd.setCursor(0, 0);
      lcd.print("Number:");
      lcd.setCursor(0, 1);
      lcd.print(num);
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
