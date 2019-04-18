#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
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
#include "Material.h"

class Shape {

private:
    std::vector<Point*> points;
    std::vector<Point*> normal;
    Material* material;
    GLuint buffer[2];

public:
    void insertPoint(Point*);
    void insertNormal(Point*);
    void setMaterial(Material*);
    Material* getMaterial();
    Point* getPoint(int);
    Point* getNormal(int);
    int getSize();
    int getNormalSize();
    void vbo();
    void draw();

};

#endif //ENGINE_SHAPE_H
