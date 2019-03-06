

#include <vector>
#include "plane.h"




Shape* plane(float size ){
    Shape *s = new Shape();

    float m = size/2;

    //1
    s->insertPoint(new Point(m,0,m));
    s->insertPoint(new Point(m,0,-m));
    s->insertPoint(new Point(-m,0,-m));

    //2
    s->insertPoint(new Point(-m,0,-m));
    s->insertPoint(new Point(-m,0,m));
    s->insertPoint(new Point(m,0,m));

    return s;
}