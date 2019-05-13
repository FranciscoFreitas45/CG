#ifndef ENGINE_SHAPE_H
#define ENGINE_SHAPE_H
#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include "/usr/local/include/IL/il.h"
#else
#include <IL/il.h>
#endif
#include <cstdlib>
#include <vector>
#include "Point.h"
#include "Material.h"


class Shape {

private:
    std::vector<Point*> points;
    std::vector<Point*> normal;
    std::vector<Point*> texture;
    Material* material;
    GLuint vertices, normals, textures, texID;

public:
    void insertPoint(Point*);
    void insertNormal(Point*);
    void setMaterial(Material*);
    void setTexID(GLuint t);
    void insertTexture(Point*);
    Material* getMaterial();
    Point* getPoint(int);
    Point* getNormal(int);
    Point* getTexture(int);
    int getSize();
    int getNormalSize();
    int getTextureSize();
    void loadTexture(string);
    void vbo();
    void draw();

};

#endif //ENGINE_SHAPE_H
