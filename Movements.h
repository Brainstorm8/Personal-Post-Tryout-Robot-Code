#ifndef MOVEMENTS_H
#define MOVEMENTS_H

class Movements {
    public:
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

    private:
        const double stepcount;  

        const double wheeldiameter; 
        const double wheelCircumference;
        const double cm_step;  

        const double distanceBetweenWheels; 


        const int enL;
        const int in1;
        const int in2;


        const int enR; 
        const int in4;
        const int in3;

        int counter_L;
        int counter_R;

        const double rightMotorCal;
        const double leftMotorCal;
};

#endif