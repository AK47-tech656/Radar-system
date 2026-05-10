# Ultrasonic Radar System with LCD & Alarm 📡

A standalone Arduino-based radar project that actively sweeps its surroundings to detect obstacles. It displays real-time telemetry (servo angle and object distance) on a 16x2 I2C LCD and triggers an audible buzzer alarm if an object gets too close.

## 🌟 Key Features
* **Active Area Sweeping:** A micro-servo continuously pans an ultrasonic sensor back and forth 180 degrees.
* **Real-Time Display:** A 16x2 I2C LCD outputs the exact angle of the servo and the distance to the nearest object in centimeters.
* **Proximity Alarm:** An active buzzer sounds automatically when an object breaches the predefined safe distance (e.g., < 20 cm).

## 🛠️ Hardware Components
* 1x Arduino Uno or Nano
* 1x HC-SR04 Ultrasonic Sensor
* 1x SG90 Micro Servo Motor
* 1x 16x2 LCD Display with I2C Module
* 1x 5V Active Buzzer
* Breadboard & Jumper Wires
* USB Cable / Power Supply

## 🔌 Wiring Guide

| Component | Pin | Arduino Pin / Connection |
| :--- | :--- | :--- |
| **HC-SR04** | VCC | 5V |
| | GND | GND |
| | TRIG | Digital Pin 9 |
| | ECHO | Digital Pin 10 |
| **Servo Motor** | VCC (Red) | 5V |
| | GND (Brown/Black) | GND |
| | Signal (Yellow/Orange) | Digital Pin 11 |
| **16x2 I2C LCD** | VCC | 5V |
| | GND | GND |
| | SDA | Analog Pin A4 (or dedicated SDA) |
| | SCL | Analog Pin A5 (or dedicated SCL) |
| **Buzzer** | Positive (+) | Digital Pin 8 |
| | Negative (-) | GND |

## 💻 Software & Libraries

Ensure you have the following libraries installed in your Arduino IDE before compiling:
1. **LiquidCrystal_I2C:** To control the display over I2C.
   * *Install:* Sketch -> Include Library -> Manage Libraries -> Search "LiquidCrystal I2C" (by Frank de Brabander).
2. **Servo:** Built-in Arduino library for motor control.
3. **Wire:** Built-in Arduino library for I2C communication.

*Note: The default I2C address in the code is usually `0x27` or `0x3F`. If your LCD doesn't display text, try swapping the address in the code.*
