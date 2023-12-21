#include <Arduino.h>

#include "Mapping.h"
#include "Movements.h"

Movements drivetrain;
Mapping map;


const byte ENCODER_L = 20;  
const byte ENCODER_R = 21;  

const byte startButton = 19;
boolean runState = false;
bool buttonPressed = false;

void ISR_button() {
  if(runState) {
    runState = false;
  } else {
    runState = true;
  }
}

void setup() 
{
  Serial.begin(9600);
  Serial.println("Starting up.");

  pinMode(ENCODER_L, INPUT_PULLUP);
  pinMode(ENCODER_R, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt (ENCODER_L), drivetrain.ISR_countL(), RISING);
  attachInterrupt(digitalPinToInterrupt (ENCODER_R), drivetrain.ISR_countR(), RISING);

  pinMode(drivetrain.getEnableL(), OUTPUT);
  pinMode(drivetrain.getEnableR(), OUTPUT);
  pinMode(drivetrain.getPin1(), OUTPUT);
  pinMode(drivetrain.getPin2(), OUTPUT);
  pinMode(drivetrain.getPin3(), OUTPUT);
  pinMode(drivetrain.getPin4(), OUTPUT);
 

  attachInterrupt(digitalPinToInterrupt(startButton), ISR_button, FALLING);
} 
 

void loop() {
  if(runState) { //put in move commands here:
    Point points[] = {Point(1,0), Point(1,2), Point(0,2), Point(2,2)};
    int lenPoints = (sizeof(points)/sizeof(points[0]));
    map.getPath(points, lenPoints, Point(0,0), 0, drivetrain);
    
    runState = false;
    Serial.print("Run complete");
  }
  delay(500);
}