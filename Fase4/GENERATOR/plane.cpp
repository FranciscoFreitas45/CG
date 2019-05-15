#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "plane.h"


Shape* plane(float size){
    Shape *s = new Shape();

    float m = size/2;
    Point* uv;
    //1
    s->insertPoint(new Point(-m,0,m));
    s->insertNormal(new Point(0,1,0));
    s->insertTexture(new Point(0,1,0));
    
    s->insertPoint(new Point(m,0,m));
    s->insertNormal(new Point(0,1,0));
    s->insertTexture(new Point(1,1,0));
    
    s->insertPoint(new Point(m,0,-m));
    s->insertNormal(new Point(0,1,0));
    s->insertTexture(new Point(1,0,0));

    //2
    s->insertPoint(new Point(-m,0,m));
    s->insertNormal(new Point(0,1,0));
    s->insertTexture(new Point(0,1,0));
    
    s->insertPoint(new Point(m,0,-m));
    s->insertNormal(new Point(0,1,0));
    s->insertTexture(new Point(1,0,0));
    

    s->insertPoint(new Point(-m,0,-m));
    s->insertNormal(new Point(0,1,0));
    s->insertTexture(new Point(0,0,0));
    return s;
}


