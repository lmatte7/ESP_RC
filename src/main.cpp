#include <Arduino.h>
#include <ESP32Servo.h>

// Calibration
int oMin = 1000; 
int oMax = 2000;
int oESC = 1000;
int oArm = 500;
uint32_t calibrationDelay = 8000;  // Calibration delay (milisecond)
uint32_t stopPulse = 0; // Stop pulse (microseconds)

Servo esc;

// the number of the LED pin
const int ledPin = 27;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 30000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  Serial.begin(115200);

  // Serial.println("Configuring ESC");
  // esc.attach(ledPin);
  // esc.writeMicroseconds(oMax);
  //   delay(calibrationDelay);
  // esc.writeMicroseconds(oMin);
  //   delay(calibrationDelay); 

  esc.attach(ledPin);
  esc.writeMicroseconds (1400);
  delay(4000);
  // Serial.println("Configuring Complete");
}

void forward() {
  esc.writeMicroseconds(1900);
}
void backward() {
  esc.writeMicroseconds(0);
}

void stop() {
  esc.writeMicroseconds(1500);
}
 
void loop(){
  Serial.println("Forward");
  forward();
  delay(3000);
  Serial.println("Stop");
  stop();
  delay(3000);
  Serial.println("Backward");
  backward();
  delay(3000);
  Serial.println("Stop");
  stop();
  delay(3000);
}