#include <Arduino.h>

#include "Mapping.h"
#include "Movements.h"
#include "MPU6050.h"
#include <vector>

Movements drivetrain;
Mapping path;
MPU6050 mpu;

const byte ENCODER_L = 18;  
const byte ENCODER_R = 19;  

const byte startButton = 2;
boolean runState = false;
bool buttonPressed = false;

int lenPoints;

std::vector<int> instructions;


    // double initTime;
    // double currTime;
    // double elapsedTime;
    // double angularPos = 0;
    // double angularVel;

void ISR_button() {
  if(runState) {
    runState = false;
  } else {
    runState = true;
  }
}

void ISR_countL() {
  drivetrain.incCountL();
}

void ISR_countR() {
  drivetrain.incCountR();
}

void readInstructions(std::vector<int> instructions) {
  const int len = instructions.size();
  for(int i = 0; i < len; i ++) {
    if(instructions.at(i) == 0) {
      drivetrain.moveForward(50, 110, mpu);
    } else if(instructions.at(i) == 90) {
      drivetrain.turnRight(90, mpu, 110);
    } else if(instructions.at(i) == 180) {
      drivetrain.moveBackward(50, 110, mpu);
    } else if(instructions.at(i) == 270) {
      drivetrain.turnLeft(90, mpu, 110);
    }
    delay(500);
  }
}

void setup() 
{
  Serial.begin(9600);

  mpu.initialize();
  mpu.setXGyroOffset(-12);
  mpu.setYGyroOffset(37);
  mpu.setZGyroOffset(72);
  mpu.setXAccelOffset(1382);
  mpu.setYAccelOffset(1066);
  mpu.setZAccelOffset(1075);

  pinMode(ENCODER_L, INPUT_PULLUP);
  pinMode(ENCODER_R, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt (ENCODER_L), ISR_countL, RISING);
  attachInterrupt(digitalPinToInterrupt (ENCODER_R), ISR_countR, RISING);

  pinMode(drivetrain.getEnableL(), OUTPUT);
  pinMode(drivetrain.getEnableR(), OUTPUT);
  pinMode(drivetrain.getPin1(), OUTPUT);
  pinMode(drivetrain.getPin2(), OUTPUT);
  pinMode(drivetrain.getPin3(), OUTPUT);
  pinMode(drivetrain.getPin4(), OUTPUT);
 

  attachInterrupt(digitalPinToInterrupt(startButton), ISR_button, FALLING);
  Serial.println("Setup complete.");
  // initTime = millis();
} 
 

void loop() {



  Serial.print(drivetrain.getCountL()); Serial.print("\t"); Serial.println(drivetrain.getCountR());
  
  if(runState) { //put in move commands here:      
      // for(int i = 0; i < 4; i++) {
      //   drivetrain.moveForward(50, 110, mpu);
      //   delay(500);
      //   drivetrain.turnLeft(90, mpu, 110);
      //   delay(500);
      // }
      // drivetrain.turnLeft(90, mpu, 110);
      drivetrain.moveForward(50, 110, mpu);
      delay(100);
      drivetrain.moveBackward(50, 110, mpu);



      // Point points[] = {Point(1,0), Point(1,2), Point(0,2), Point(2,2)};
      // lenPoints = (sizeof(points)/sizeof(points[0]));

      // drivetrain.moveForward(25, 110);
      // instructions = path.getPath(points, lenPoints, Point(0,0), 0);
      // readInstructions(instructions);

      runState = false;
      Serial.println("Run complete");
  }
  delay(500);
}