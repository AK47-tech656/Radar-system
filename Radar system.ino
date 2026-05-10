#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int trigPin = 10;
const int echoPin = 11;
const int servoPin = 9;
const int buzzerPin = 8;


const int THRESHOLD_DISTANCE = 35; 


Servo radarServo;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- Variables ---
int angle = 0;
int sweepDirection = 1; // 1 moves forward, -1 moves backward

void setup() {
  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Attach the servo
  radarServo.attach(servoPin);
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Boot screen
  lcd.setCursor(0, 0);
  lcd.print("System Booting..");
  delay(2000);
  lcd.clear();
}

// Function to calculate distance from the ultrasonic sensor
int getDistance() {
  // Send a 10 microsecond ping
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure how long it takes for the echo to return
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm (Speed of sound is 0.034 cm/microsecond)
  int distance = duration * 0.034 / 2;
  
  // If distance is 0 (sensor error or out of range), return a high number
  if (distance == 0) return 999; 
  return distance;
}

void loop() {
  int distance = getDistance();
  
  // --- DETECTION MODE ---
  if (distance <= THRESHOLD_DISTANCE) {
    // Sound the alarm
    digitalWrite(buzzerPin, HIGH); 
    
    // Update LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INTRUDER ALERT!");
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(distance);
    lcd.print("cm A:");
    lcd.print(angle);
    lcd.print((char)223); // Prints the degree symbol (°)
    
    // Keep the servo locked in place and wait a moment
    delay(500); 
  } 
  
  // --- SCANNING MODE ---
  else {
    // Turn off the alarm
    digitalWrite(buzzerPin, LOW); 
    
    // Update LCD Screen
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scanning Area...");
    lcd.setCursor(0, 1);
    lcd.print("Angle: ");
    lcd.print(angle);
    lcd.print((char)223); // Prints the degree symbol (°)
    
    // Move the servo to the current angle
    radarServo.write(angle);
    
    // Increase or decrease the angle for the next loop
    // Moves in steps of 5 degrees for a smoother sweep
    angle = angle + (sweepDirection * 5); 
    
    // If the servo reaches the edge (180 or 0), reverse direction
    if (angle >= 180 || angle <= 0) {
      sweepDirection = -sweepDirection;
    }
    
    // Wait a short moment to let the servo reach the position
    delay(100); 
  }
}