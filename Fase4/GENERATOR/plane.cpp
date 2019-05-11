#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "plane.h"


Shape* plane(float size){
    Shape *s = new Shape();

    float m = size/2;
    float uv[12];
    //1
    s->insertPoint(new Point(-m,0,m));
    s->insertNormal(new Point(0,1,0));
    uv[0] = 0;
    uv[1] = 0;
    s->insertTexture(uv);
    
    s->insertPoint(new Point(m,0,m));
    s->insertNormal(new Point(0,1,0));
    uv[2] = 1;
    uv[3] = 0;
    s->insertTexture(uv+2);
    
    s->insertPoint(new Point(m,0,-m));
    s->insertNormal(new Point(0,1,0));
    uv[4] = 1;
    uv[5] = 1;
    s->insertTexture(uv+4);

    //2
    s->insertPoint(new Point(-m,0,m));
    s->insertNormal(new Point(0,1,0));
    uv[6] = 0;
    uv[7] = 0;
    s->insertTexture(uv+6);
    
    s->insertPoint(new Point(m,0,-m));
    s->insertNormal(new Point(0,1,0));
    uv[8] = 1;
    uv[9] = 1;
    s->insertTexture(uv+8);
    

    s->insertPoint(new Point(-m,0,-m));
    s->insertNormal(new Point(0,1,0));
    uv[10] = 0;
    uv[11] = 1;
    s->insertTexture(uv+10);
    return s;
}


