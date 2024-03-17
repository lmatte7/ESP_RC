#include <Arduino.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"
#include <PS4Controller.h>

// Calibration
int oMin = 1000; 
int oMax = 2000;
int oESC = 1000;
int oArm = 500;
uint32_t calibrationDelay = 8000;  // Calibration delay (milisecond)
uint32_t stopPulse = 0; // Stop pulse (microseconds)

Servo esc;
Servo motor2;
Servo flipper;

BluetoothSerial SerialBT;

// the number of the LED pin
const int ledPin = 13;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 30000;
const int ledChannel = 0;
const int resolution = 8;

uint8_t playStationController[] = {0x90,0x89,0x5F,0x25,0xC0,0xA1};


int motorSpeed1, motorSpeed2, lStickY, rStickY = 0;

void armESC() {
  Serial.println("Arming ESC");
  esc.attach(ledPin);
  esc.writeMicroseconds (1400);
  delay(1000);
  Serial.println("ESC Armed");
}

void armMotor() {
  motor2.attach(12);
  motor2.writeMicroseconds (1400);
  delay(1000);
}

void pairPS4() {
  SerialBT.begin();
  SerialBT.unpairDevice(playStationController);
  SerialBT.end();
  PS4.begin("D4:25:8B:F9:A7:62");
}
void forward() {
  esc.writeMicroseconds(1900);
}
void backward() {
  esc.writeMicroseconds(0);
}

void stop() {
  esc.writeMicroseconds(1500);
  motor2.writeMicroseconds(1500);
} 
void stopAll() {
  esc.writeMicroseconds(1500);
  motor2.writeMicroseconds(1500);
}

void stop1() {
  esc.writeMicroseconds(1500);
}

void stop2() {
  motor2.writeMicroseconds(1500);
}

void flip() {
  flipper.writeMicroseconds(2000);
}
 
void flipReset() {
  flipper.write(1500);
}

void setup(){
  Serial.begin(115200);

  pairPS4();
  flipper.attach(14);

  armESC();
  armMotor();
  stop();
}


 
void loop(){
  if(PS4.isConnected()) {
    lStickY = PS4.LStickY();
    if(lStickY < -50 || lStickY > 50) {
      lStickY *= 100;
      motorSpeed1 = (int)map(lStickY, -128*100, 127*100, 800, 1900);
      Serial.printf("Stick %d, Motor %d\n", lStickY, motorSpeed1);
      esc.writeMicroseconds(motorSpeed1);
    } else {
      stop1();
    }
    rStickY = PS4.RStickY();
    if(rStickY < -50 || rStickY > 50) {
      rStickY *= 100;
      motorSpeed2 = (int)map(rStickY, -128*100, 127*100, 800, 1900);
      Serial.printf("Stick %d, Motor %d\n", rStickY, motorSpeed2);
      motor2.writeMicroseconds(motorSpeed2);
    } else {
      stop2();
    }
  } else {
    stopAll();
  }

  if(PS4.R2()) {
    flip();
  } else {
    flipReset();
  }
}