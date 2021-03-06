#define _USE_MATH_DEFINES
#include <cmath>
#include "cylinder.h"
#include "../src/Shape.h"
#include <math.h>




Shape* cylinder(float radius, float height, int slices, int stacks) {
    Shape *s = new Shape();
    float alfa, b;
    float step = height/stacks;
    float reduction = radius/stacks;
    float base;
    float topo;
    float r, r_in;
    float ang = 2*M_PI/slices;
    for(int i=0; i<slices; i++){
        b = 0.01*i;
        alfa =  i*(M_PI*2/slices);

        //base
        s->insertPoint(new Point(radius*cos(alfa+ang),0,radius*sin(alfa+ang)));
        s->insertNormal(new Point(0,-1,0));
        s->insertPoint(new Point(0,0,0));
        s->insertNormal(new Point(0,-1,0));
        s->insertPoint(new Point(radius*cos(alfa),0,radius*sin(alfa)));
        s->insertNormal(new Point(0,-1,0));

        //topo
        s->insertPoint(new Point(radius*cos(alfa),height,radius*sin(alfa)));
        s->insertNormal(new Point(0,1,0));
        s->insertPoint(new Point(0,height,0));
        s->insertNormal(new Point(0,1,0));
        s->insertPoint(new Point(radius*cos(alfa+ang),height,radius*sin(alfa+ang)));
        s->insertNormal(new Point(0,1,0));

        base = -step;
        topo = 0;
        r = radius;
        for(int j=1; j<=stacks; j++){
            base += step;
            topo += step;

            s->insertPoint(new Point(r*cos(alfa),base,r*sin(alfa)));
            s->insertNormal(new Point(cos(alfa),0,sin(alfa)));
            s->insertPoint(new Point(r*cos(alfa),topo,r*sin(alfa)));
            s->insertNormal(new Point(cos(alfa),0,sin(alfa)));
            s->insertPoint(new Point(r*cos(alfa+ang),base,r*sin(alfa+ang)));
            s->insertNormal(new Point(cos(alfa+ang),0,sin(alfa+ang)));

            s->insertPoint(new Point(r*cos(alfa),topo,r*sin(alfa)));
            s->insertNormal(new Point(cos(alfa),0,sin(alfa)));
            s->insertPoint(new Point(r*cos(alfa+ang),topo,r*sin(alfa+ang)));
            s->insertNormal(new Point(cos(alfa+ang),0,sin(alfa+ang)));
            s->insertPoint(new Point(r*cos(alfa+ang),base,r*sin(alfa+ang)));
            s->insertNormal(new Point(cos(alfa+ang),0,sin(alfa+ang)));
        }
    }
    return s;
}

