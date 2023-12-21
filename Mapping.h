#ifndef MAPPING_H
#define MAPPING_H

#include "Movements.h"
#include "Point.h"

class Mapping {
    public:
        Mapping();

        void getPath(Point, int, Point, int);

        int getPredictedDirection(int, int);

    private:
        Movements drivetrain;
};

#endif