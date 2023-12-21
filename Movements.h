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
};

#endif