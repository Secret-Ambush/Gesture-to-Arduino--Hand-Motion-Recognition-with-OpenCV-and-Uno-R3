# gesture_detect.py
# Prototype: Detect waving hand → send "HI" to Arduino Uno
# Author: Riddhi Goswami (2025)

import cv2
import serial
import time
import numpy as np
from collections import deque

# --- Arduino Serial Setup ---
# Replace 'COM3' with your Arduino port (Linux: '/dev/ttyUSB0' or '/dev/ttyACM0')
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Allow Arduino to reset

# --- OpenCV Setup ---
cap = cv2.VideoCapture(0)
cap.set(3, 640)  # Width
cap.set(4, 480)  # Height

# Track movement history (for wave detection)
motion_history = deque(maxlen=10)

def detect_wave(contour):
    """Return True if contour centroid moves left-right like a wave."""
    if contour is None:
        return False

    # Compute centroid
    M = cv2.moments(contour)
    if M["m00"] == 0:
        return False
    cx = int(M["m10"] / M["m00"])
    motion_history.append(cx)

    # Check oscillation (left-right movement)
    if len(motion_history) == motion_history.maxlen:
        diff = max(motion_history) - min(motion_history)
        if diff > 100:  # Threshold for waving
            return True
    return False

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convert to grayscale + blur
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (15, 15), 0)

    # Simple thresholding for hand region (tune threshold!)
    _, thresh = cv2.threshold(blur, 50, 255, cv2.THRESH_BINARY_INV+cv2.THRESH_OTSU)

    # Find largest contour (assume hand)
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if contours:
        hand = max(contours, key=cv2.contourArea)
        x, y, w, h = cv2.boundingRect(hand)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

        if detect_wave(hand):
            print("WAVE detected → Sending HI")
            arduino.write(b"HI\n")  # Send to Arduino
            motion_history.clear()  # Reset so it doesn’t spam

    # Show debug windows
    cv2.imshow("Frame", frame)
    cv2.imshow("Thresh", thresh)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
arduino.close()
cv2.destroyAllWindows()
