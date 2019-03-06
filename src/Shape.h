

#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include <vector>
#include "Point.h"

class Shape {

private:
    std::vector<Point*> Points;

public:
    void insertPoint(Point *p);
    Point* getPoint(int i);
    int getSize();





};


#endif //ENGINE_SHAPE_H
