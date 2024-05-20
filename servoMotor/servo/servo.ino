#include <ESP32Servo.h>

Servo myServo;
int servoPin = 13;

void setup() {
  myServo.attach(servoPin);
  myServo.write(0);
}

void loop() {
  myServo.write(360); // Rotate the servo to 90 degrees
  delay(1000);       // Wait for 1 second
  // myServo.write(0);  // Rotate the servo back to 0 degrees
  delay(1000);       // Wait for 1 second
}
