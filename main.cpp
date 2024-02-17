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

int straightSpeed = 200;
int turningSpeed = 200;

const int waitTime = 250; //time between movements in ms

std::vector<instruction> instructions;

Point startingPoint;

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

void readInstructions(std::vector<instruction> instructions) {
  const int len = instructions.size();
  for(int i = 0; i < len; i ++) {
    if(instructions.at(i).direction == 0) {
      drivetrain.moveForward(50*instructions.at(i).multiplier, straightSpeed, mpu);
    } else if(instructions.at(i).direction == -90) {
      drivetrain.turnRight(90*instructions.at(i).multiplier, turningSpeed, mpu);
    } else if(instructions.at(i).direction == 180) {
      drivetrain.moveBackward(50*instructions.at(i).multiplier, straightSpeed, mpu);
    } else if(instructions.at(i).direction == 90) {
      drivetrain.turnLeft(90*instructions.at(i).multiplier, turningSpeed, mpu);
    }
    Serial.println("movement complete");
    delay(waitTime);
  }
}

void setup() 
{
  Serial.begin(9600);

  mpu.initialize();
  mpu.setXGyroOffset(-9);
  mpu.setYGyroOffset(31);
  mpu.setZGyroOffset(88);
  mpu.setXAccelOffset(1505);
  mpu.setYAccelOffset(1140);
  mpu.setZAccelOffset(1079);

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
} 
 

void loop() {

  Serial.print(drivetrain.getCountL()); Serial.print("\t");
  Serial.println(drivetrain.getCountR());

  
  if(runState) { //put in move commands here:
      delay(200);      
      // for(int i = 0; i < 4; i++) {
      //   // drivetrain.moveForward(50, straightSpeed, mpu);
      //   // delay(waitTime);
      //   drivetrain.turnRight(90, turningSpeed, mpu);
      //   delay(waitTime);

      //   // drivetrain.moveBackward(50, straightSpeed, mpu);
      //   // delay(waitTime);
      //   drivetrain.turnLeft(90, turningSpeed, mpu);
      //   delay(waitTime);
      // }

      
      startingPoint = Point(2,0);
      Point points[] = {Point(3,0), Point(3,1), Point(2,1), Point(3,1), Point(3,3), Point(3,2), Point(1,2), Point(1,1), Point(0,1), Point(0,0), Point(0,1), Point(1,1),Point(1,3), Point(2,3)};
      lenPoints = (sizeof(points)/sizeof(points[0]));

      drivetrain.moveForward(25, straightSpeed, mpu);
      delay(waitTime);
      instructions = path.getPath(points, lenPoints, startingPoint, 0);
      readInstructions(instructions);

      runState = false;
      Serial.println("Run complete");
  }
  delay(100);
}