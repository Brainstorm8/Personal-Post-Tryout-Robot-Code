#ifndef MAPPING_H
#define MAPPING_H

#include "Movements.h"
#include "Point.h"
#include <vector>

struct instruction{
    int direction;
    int multiplier;
};

class Mapping {
    public:

        Mapping();

        std::vector<instruction> getPath(Point[], int, Point, int);

        int getTurnDirection(int, int);

        int getAbsoluteVal(int num);

    private:

};

#endif