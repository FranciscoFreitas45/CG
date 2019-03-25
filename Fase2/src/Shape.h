#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H

#include <vector>
#include "Point.h"

class Shape {

private:
    std::vector<Point*> Points;
    GLuint buffer;

public:
    void insertPoint(Point*);
    Point* getPoint(int);
    int getSize();

};

#endif //ENGINE_SHAPE_H
