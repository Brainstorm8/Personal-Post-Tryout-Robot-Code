#ifndef MOVEMENTS_H
#define MOVEMENTS_H

class Movements {
    public:
        Movements(); //constructor

        int cmToSteps(double);

        void setDirection(int);

        void move(int, int);

        void moveForward(int, int);

        void moveBackward(int, int);

        void turn(double, int);

        void turnLeft(double, int);

        void turnRight(double, int);

        void ISR_countL();

        void ISR_countR();

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

        int counter_L = 0;
        int counter_R = 0;

        double rightMotorCal;
        double leftMotorCal;
};

#endif