# **“Gesture-to-Arduino: Hand Motion Recognition with OpenCV and Uno R3”**

---

## 📖 Overview

This project bridges **computer vision** and **embedded systems**. A webcam detects simple hand gestures using **OpenCV** on a PC/Raspberry Pi. Recognised gestures are sent via **serial communication** to an **Arduino Uno R3**, which controls outputs such as an **LCD display**, **buzzer**, and **LED dot matrix (MAX7219)**.

The first milestone is simple:

* Wave your hand → Arduino displays `"Hi"`
* Show fingers (1–5) → Arduino displays the number

Later phases extend this to auditory feedback (buzzer) and visual graphics (LED matrix).

---

## 🚀 Features (Planned Milestones)

1. **Phase 1 – Core**

   * Detect waving and finger count gestures in OpenCV
   * Send commands via serial to Arduino
   * Display results on LCD

2. **Phase 2 – Feedback**

   * Add buzzer signals (short beep for wave, `n` beeps for number)

3. **Phase 3 – Visual Enhancement**

   * Add MAX7219 LED matrix:

     * Hand icon for wave
     * Numeric display for finger count

4. **Stretch Goals**

   * Servo robot arm that waves back
   * Real-time clock integration (e.g., “Hi! Time: 14:35”)
   * Mode switching with IR remote

---

## 🛠️ Hardware Requirements

* Arduino Uno R3
* USB cable for PC ↔ Arduino communication
* 16x2 LCD display module
* Active buzzer module
* MAX7219 LED dot matrix
* Jumper wires + breadboard
* Webcam (for gesture detection)

---

## 💻 Software Requirements

* Python 3.x
* OpenCV (`pip install opencv-python`)
* PySerial (`pip install pyserial`)
* Arduino IDE + LiquidCrystal library + LedControl/MD\_MAX72XX library

---

## 📂 Project Structure

```
gesture-to-arduino/
│
├── python/
│   └── gesture_detect.py   # OpenCV gesture recognition & serial comms
│
├── arduino/
│   └── lcd_serial.ino      # Arduino sketch for LCD + serial listener
│
├── README.md
└── docs/                   # Future wiring diagrams, images, notes
```

---

## 🔧 How It Works

1. **Python OpenCV** reads webcam frames and analyses hand movement.
2. Detected gestures are converted into short commands (`"HI"`, `"NUM:3"`, etc.).
3. Commands are sent over serial USB to Arduino.
4. Arduino interprets the commands and updates LCD/buzzer/LED matrix accordingly.

---

## 📈 Roadmap

* [x] Prototype waving detection
* [ ] Finger counting (basic convex hull method)
* [ ] LCD integration
* [ ] Buzzer feedback
* [ ] LED matrix animations
* [ ] Stretch goals

---
