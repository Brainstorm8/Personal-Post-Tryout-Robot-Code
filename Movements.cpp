#include <Arduino.h>
#include "Movements.h"

Movements::Movements() {
    stepcount = 20.00;  // 20 Slots in disk, change if different

    // Constant for wheel diameter
    wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different
    wheelCircumference = (wheeldiameter * 3.14) / 10; // Calculate wheel wheelCircumference in cm
    cm_step = wheelCircumference / stepcount;  // CM per Step

    distanceBetweenWheels = 13.2; //distance between wheels in cm

    // Left Motor

    enL = 8;
    in1 = 7;
    in2 = 6;

    // Right Motor

    enR = 3; 
    in4 = 4;
    in3 = 5;

    counter_L = 0;
    counter_R = 0;

    rightMotorCal = 1.0;
    leftMotorCal = .77;
}



// Function to convert from centimeters to steps
int Movements::cmToSteps(double cm) {

    int result;  // Final calculation result

    double f_result = cm / cm_step;  // Calculate result as a double
    result = (int) f_result; // Convert to an integer (note this is NOT rounded)
    
    return result;  // End and return result
}


void Movements::setDirection(int dir) {
    if(dir == 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);

        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);

    } else if (dir == 180) {

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);

        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    } else if (dir == 270) { //turning left

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);

        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    } else if (dir == 90) { //turning right

        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);

        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
}



void Movements::move(int cm, int mspeed) {
    int steps = cmToSteps(cm);
    counter_L = 0;  //  reset counter A to zero
    counter_R = 0;  //  reset counter B to zero
    
    // Go forward until step value is reached
    while (steps > counter_L && steps > counter_R) {
    
        if (steps > counter_L) {
        analogWrite(enL, mspeed*leftMotorCal);
        } else {
        analogWrite(enL, 0);
        }
        if (steps > counter_R) {
        analogWrite(enR, mspeed);
        } else {
        analogWrite(enR, 0);
        }
    }

    // Stop when done
    analogWrite(enL, 0);
    analogWrite(enR, 0);
    counter_L = 0; 
    counter_R = 0;  
    
    delay(500);
}

void Movements::moveForward(int cm, int mspeed) {
    setDirection(0);
    move(cm, mspeed);
} 

void Movements::moveBackward(int cm, int mspeed) {
    setDirection(180);
    move(cm, mspeed);
} 

void Movements::turn(double degrees, int mspeed) { //turn to a specific angular position
    const double turning_circumference = 3.14*distanceBetweenWheels; //circumference in cm

    double arcLength = (degrees/360.0)*turning_circumference; //arc length of turn in cm

    move(arcLength, mspeed);
} 

void Movements::turnLeft(double degrees, int mspeed) {
    setDirection(270);
    turn(degrees, mspeed);
}

void Movements::turnRight(double degrees, int mspeed) {
    setDirection(90);
    turn(degrees, mspeed);
}


void Movements::ISR_countL()  {
    counter_L++;
} 

// Motor B pulse count ISR
void Movements::ISR_countR()  {
    counter_R++; 
}

int Movements::getCountL() {
    return counter_L;
}

int Movements::getCountR() {
    return counter_R;
}

int Movements::getEnableL() {
    return enL;
}

int Movements::getEnableR() {
    return enR;
}

int Movements::getPin1() {
    return in1;
}

int Movements::getPin2() {
    return in2;
}

int Movements::getPin3() {
    return in3;
}

int Movements::getPin4() {
    return in4;
}