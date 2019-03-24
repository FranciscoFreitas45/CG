

#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include <vector>
#include <GL/gl.h>
#include "Point.h"

class Shape {

private:
    std::vector<Point*> Points;
    GLuint buffer;

public:
    void insertPoint(Point *p);
    Point* getPoint(int i);
    int getSize();
    void vectorToArray();





};


#endif //ENGINE_SHAPE_H
