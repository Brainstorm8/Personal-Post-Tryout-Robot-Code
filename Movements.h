#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <MPU6050.h>

class Movements {
    public:
        Movements(); //constructor

        int cmToSteps(double);

        void setDirection(int);

        void move(int, int, boolean, MPU6050);

        void moveForward(int, int, MPU6050);

        void moveBackward(int, int, MPU6050);

        void turn(double, int,  MPU6050);

        void turnLeft(double, int, MPU6050);

        void turnRight(double, int, MPU6050);

        void incCountL();

        void incCountR();

        int getCountL();

        int getCountR();

        int getEnableL();

        int getEnableR();

        int getPin1();

        int getPin2();

        int getPin3();

        int getPin4();

    private:
        double stepcount;  

        double wheeldiameter; 
        double wheelCircumference;
        double cm_step;  

        double distanceBetweenWheels; 


        int enL;
        int in1;
        int in2;


        int enR; 
        int in4;
        int in3;

        int counter_L;
        int counter_R;

        double rightMotorCal;
        double leftMotorCal;

        double backRightMotorCal;
        double backLeftMotorCal;

};

#endif