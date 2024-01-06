#ifndef MAPPING_H
#define MAPPING_H

#include "Movements.h"
#include "Point.h"
#include <vector>

class Mapping {
    public:
        Mapping();

        std::vector<int> getPath(Point[], int, Point, int);

        int getPredictedDirection(int, int);

        int getAbsoluteVal(int num);

    private:

};

#endif