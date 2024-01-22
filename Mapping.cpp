#include "Mapping.h"
#include <vector> //got from ArduinoSTL library


Mapping::Mapping() {

}

int getPredictedDirection(int currentDirection, int turnDirection);

std::vector<instruction> Mapping::getPath(Point cords[], int len, Point pInitial, int init_Direction) { //note that the input points must draw ONLY vertical or horizontal lines
    int deltaX;
    int deltaY;
    int final_Direction;
    int current_Direction = init_Direction;
    int turn_Direction;
    bool goReverse;
    instruction newInstruction;
    Point current_Point = pInitial;

    std::vector<instruction> instructions;


    // int numInstructions = std::extent<decltype(cords)>::value;

    for (int i = 0; i < len; i++) { //goes through all the list of cords
        deltaX = cords[i].getX() - current_Point.getX();
        deltaY = cords[i].getY() - current_Point.getY();


        if(deltaX > 0) { //right
            final_Direction = -90;
        } else if(deltaX < 0) { //left
            final_Direction = 90;
        } else if(deltaY > 0) { //up
            final_Direction = 0;
        } else if(deltaY < 0) { //down
            final_Direction = 180;
        } else {
            final_Direction = current_Direction;
        }

        goReverse = false;

        turn_Direction = getTurnDirection(current_Direction, final_Direction); //gives turning direction
        if(turn_Direction == 90) {
            newInstruction.direction = 90;
            newInstruction.multiplier = 1;
            instructions.push_back(newInstruction);

            current_Direction = final_Direction;
        } else {
            
            if(getAbsoluteVal(turn_Direction) == 180) {
                goReverse = true;
            } else {

                if(turn_Direction == -90) {
                    newInstruction.direction = -90;
                    newInstruction.multiplier = 1;
                    instructions.push_back(newInstruction);
                    
                    current_Direction = final_Direction;
                }
            }
        }
        newInstruction.multiplier = 0;
        if(deltaX != 0) { //Move forwards and updates position
            for(int j = 0; j < getAbsoluteVal(deltaX); j++) {
                if(goReverse) {
                    newInstruction.direction = 180;
                    newInstruction.multiplier += 1;
                } else {
                    newInstruction.direction = 0;
                    newInstruction.multiplier += 1;
                }

                if(deltaX > 0) {
                    current_Point.incX();
                } else if (deltaX < 0) {
                    current_Point.decX();
                }
                
            }
            instructions.push_back(newInstruction);
        } else if(deltaY != 0) {
            for(int j = 0; j < getAbsoluteVal(deltaY); j++) {
                if(goReverse) {
                    newInstruction.direction = 180;
                    newInstruction.multiplier += 1;
                } else {
                    newInstruction.direction = 0;
                    newInstruction.multiplier += 1;
                }

                if(deltaY > 0) {
                    current_Point.incY();
                } else if (deltaY < 0) {
                    current_Point.decY();
                }
            }
            instructions.push_back(newInstruction);
        }
    }
    return instructions;
}

int Mapping::getTurnDirection(int currentDirection, int endDirection) {
    int turnDirection = endDirection - currentDirection;
    if(turnDirection > 180) {
        turnDirection -= 360;
    } else if (turnDirection < -180) {
        turnDirection += 360;
    }
    return turnDirection;
}

int Mapping::getAbsoluteVal(int num) {
    if(num < 0) {
        num *= -1;
    }

    return num;
} 
