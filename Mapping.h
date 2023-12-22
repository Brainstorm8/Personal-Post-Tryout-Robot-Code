#ifndef MAPPING_H
#define MAPPING_H

#include "Movements.h"
#include "Point.h"

class Mapping {
    public:
        Mapping();

        void getPath(Point[], int, Point, int, Movements);

        int getPredictedDirection(int, int);

        int getAbsoluteVal(int num);

    private:

};

#endif