#ifndef POINT_H
#define POINT_H

class Point {
    public:
        Point(int, int);

        int getX();

        int getY();

        void incX();

        void decX();

        void incY();

        void decY();
    private:
        int xCord;
        int yCord;
};

#endif