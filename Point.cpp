#include "Point.h"

Point::Point(int x, int y) {
    xCord = x;
    yCord = y;
};

int Point::getX() {
    return xCord;
}

int Point::getY() {
    return yCord;
}

void Point::incX() {
    xCord++;
}

void Point::decX() {
    xCord--;
}

void Point::incY() {
    yCord++;
}

void Point::decY() {
    yCord--;
}