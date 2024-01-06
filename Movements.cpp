#include <Arduino.h>
#include "Movements.h"

Movements::Movements() {
    stepcount = 620.0; //measured
    wheeldiameter = 6.70; // Wheel diameter in cm
    wheelCircumference = wheeldiameter * 3.14; // Calculate wheel wheelCircumference in cm
    cm_step = wheelCircumference / stepcount;  // CM per Step

    distanceBetweenWheels = 20.4; //distance between wheels in cm

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

    rightMotorCal = 1.00;
    leftMotorCal = .98;
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
    } else if (dir == 90) { //turning left

        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);

        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    } else if (dir == -90) { //turning right

        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);

        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }
}

void Movements::move(int cm, int maxSpeed, boolean goingForward, MPU6050 mpu) {
    int steps = cmToSteps(cm);

    const double startTime = millis();
    double initTime = startTime;
    double currTime = startTime;
    double elapsedTime;

    double angularVel = 0;
    double angularPos = 0;

    double errorA = 0;
    double kpA = 9.5;

    double errorD = steps;
    double kpD = 1.9;
    double lpower;
    double rpower;

    counter_L = 0;  //  reset counter A to zero
    counter_R = 0;  //  reset counter B to zero
    
    // Go forward until step value is reached
    while (abs(errorD) > 1.0) { //failsafe, ends movement if it takes longer than 5 seconds && (currTime - startTime) < 5000
        currTime = millis();
        elapsedTime = currTime - initTime;
        if(elapsedTime > 100) { //every 100ms
            angularVel = mpu.getRotationZ()/131.0;
            angularPos = angularVel*(elapsedTime/1000.0);

            initTime = currTime;
        }

        errorA = angularPos;

        errorD = steps - (counter_L + counter_R)/2.0; //averaging encoder data

        lpower = errorD*kpD;
        rpower = errorD*kpD;
        
        if(rpower > maxSpeed) {
            rpower = maxSpeed;
        }

        if(lpower > maxSpeed) {
            lpower = maxSpeed;
        }

        // if(errorA > 0) {
        //     lpower += errorA*kpA;
        //     rpower -= errorA*kpA;
        // } else if (errorA < 0) {
        //     lpower -= errorA*kpA;
        //     rpower += errorA*kpA;
        // }

        if(rpower > 255) {
            rpower = 255;
        } else if(rpower < 0) { //no protection for overshoot
            rpower = 0;
        }

        if(lpower > 255) {
            lpower = 255;
        } else if(lpower < 0) { //no protection for overshoot
            lpower = 0;
        }


        analogWrite(enL, lpower*leftMotorCal);
        analogWrite(enR, rpower*rightMotorCal);

        Serial.print(rpower); Serial.print("\t");
        Serial.print(lpower); Serial.print("\t");
        Serial.println(errorD);
    }


    analogWrite(enL, 0);
    analogWrite(enR, 0);
    counter_L = 0; 
    counter_R = 0;  
}

void Movements::moveForward(int cm, int maxSpeed, MPU6050 mpu) {
    setDirection(0);
    move(cm, maxSpeed, true, mpu);
}

void Movements::moveBackward(int cm, int maxSpeed, MPU6050 mpu) {
    setDirection(180);
    move(cm, maxSpeed, false, mpu);
}

void Movements::turn(double degrees, MPU6050 mpu, int maxSpeed) {
    double initTime = millis();
    double currTime = millis();
    double elapsedTime;
    double angularPos = 0;
    double angularVel;
    double deltaTheta = degrees - angularPos;
    double intDeltaTheta = 0;

    const double startTime = millis();

    double kp = 6.0;
    double ki = .50;

    double mpower;

    while(abs(deltaTheta) > 1) { //failsafe, end the turn if it takes longer than 5 seconds  && (currTime - startTime) < 5000
        currTime = millis();
        elapsedTime = currTime - initTime;



        deltaTheta = degrees - angularPos; //error

        mpower = kp*deltaTheta + ki*intDeltaTheta; //adding integral term would cause robot to go haywire

        if(mpower < 0) {
            mpower = abs(mpower);
            setDirection(-90);
        } else if(mpower > 0) {
            setDirection(90);
        }

        if(mpower > maxSpeed) {
            mpower = maxSpeed;
        } 



        analogWrite(enL, mpower*leftMotorCal);
        analogWrite(enR, mpower*rightMotorCal);
        if(elapsedTime > 100) {
            angularVel = mpu.getRotationZ()/131.0;
            angularPos += angularVel*(elapsedTime/1000.0); //integral of angular velocity with respect to time
            intDeltaTheta += deltaTheta*(elapsedTime/1000.0); //integral of error with respect to time
            initTime = currTime;
        }
        Serial.print(angularPos); Serial.print("\t");
        Serial.print(ki*intDeltaTheta); Serial.print("\t");
        Serial.println(deltaTheta);
    }
    analogWrite(enL, 0);
    analogWrite(enR, 0);

    delay(500);
}

void Movements::turnLeft(double degrees, MPU6050 mpu, int maxSpeed) {
    setDirection(90);
    turn(degrees, mpu, maxSpeed);
}

void Movements::turnRight(double degrees, MPU6050 mpu, int maxSpeed) {
    setDirection(-90);
    turn(-degrees, mpu, maxSpeed);
}

void Movements::incCountL()  {
    counter_L++;
} 

// Motor B pulse count ISR
void Movements::incCountR()  {
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