#include "Mapping.h"
#include <vector> //got from ArduinoSTL library


Mapping::Mapping() {

}

int getPredictedDirection(int currentDirection, int angleOffset);

std::vector<int> Mapping::getPath(Point cords[], int len, Point pInitial, int int_Direction) { //note that the input points must draw ONLY vertical or horizontal lines
    int deltaX;
    int deltaY;
    int final_Direction;
    int current_Direction = int_Direction;
    int predicted_Direction;
    bool goReverse;
    Point current_Point = pInitial;

    std::vector<int> instructions;


    // int numInstructions = std::extent<decltype(cords)>::value;

    for (int i = 0; i < len; i++) { //goes through all the list of cords
        deltaX = cords[i].getX() - current_Point.getX();
        deltaY = cords[i].getY() - current_Point.getY();


        if(deltaX > 0) { //right
            final_Direction = 90;
        } else if(deltaX < 0) { //left
            final_Direction = 270;
        } else if(deltaY > 0) { //up
            final_Direction = 0;
        } else if(deltaY < 0) { //down
            final_Direction = 180;
        } else {
            final_Direction = current_Direction;
        }

        goReverse = false;

        predicted_Direction = getPredictedDirection(current_Direction, 90); //gives turning direction
        if(predicted_Direction == final_Direction) {
            // drivetrain.turnRight(90, 110);
            instructions.push_back(90);
            current_Direction = final_Direction;
        } else {
            predicted_Direction = getPredictedDirection(current_Direction, 180);
            
            if(predicted_Direction == final_Direction) {
                goReverse = true;
            } else {
                predicted_Direction = getPredictedDirection(current_Direction, 270);

                if(predicted_Direction == final_Direction) {
                    // drivetrain.turnLeft(90, 110);
                    instructions.push_back(270);
                    current_Direction = final_Direction;
                }
            }
        }

        if(deltaX != 0) { //Move forwards and updates position
            for(int j = 0; j < getAbsoluteVal(deltaX); j++) {
                if(goReverse) {
                    // drivetrain.moveBackward(50, 110);
                    instructions.push_back(180);
                } else {
                    // drivetrain.moveForward(50, 110);
                    instructions.push_back(0);
                }

                if(deltaX > 0) {
                    current_Point.incX();
                } else if (deltaX < 0) {
                    current_Point.decX();
                }
                
            }
        } else if(deltaY != 0) {
            for(int j = 0; j < getAbsoluteVal(deltaY); j++) {
                if(goReverse) {
                    // drivetrain.moveBackward(50, 110);
                    instructions.push_back(180);
                } else {
                    // drivetrain.moveForward(50, 110);
                    instructions.push_back(0);
                }

                if(deltaY > 0) {
                    current_Point.incY();
                } else if (deltaY < 0) {
                    current_Point.decY();
                }
            }
        }
    }
    return instructions;
}

int Mapping::getPredictedDirection(int currentDirection, int angleOffset) {
    int prediction = currentDirection + angleOffset;
    if(prediction >= 360) {
        prediction -= 360;
    }
    return prediction;
}

int Mapping::getAbsoluteVal(int num) {
    if(num < 0) {
        num *= -1;
    }

    return num;
} 
