#define _USE_MATH_DEFINES
#include <cmath>
#include "cone.h"
#include "../src/Shape.h"
#include <math.h>
#include <vector>

using std::vector;


Shape* cone(float radius, float height, int slices, int stacks) {
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
        
        s->insertPoint(new Point(radius*cos(alfa+ang),0,radius*sin(alfa+ang)));
        s->insertPoint(new Point(0,0,0));
        s->insertPoint(new Point(radius*cos(alfa),0,radius*sin(alfa)));
        
        base = -step;
        topo = 0;
        r = radius;
        r_in = radius - reduction;
                       
        for(int j=1; j<=stacks; j++){
            base += step;
            topo += step;
            s->insertPoint(new Point(r*cos(alfa),base,r*sin(alfa)));
            s->insertPoint(new Point(r_in*cos(alfa),topo,r_in*sin(alfa)));
            s->insertPoint(new Point(r*cos(alfa+ang),base,r*sin(alfa+ang)));
           
            s->insertPoint(new Point(r_in*cos(alfa),topo,r_in*sin(alfa)));
            s->insertPoint(new Point(r_in*cos(alfa+ang),topo,r_in*sin(alfa+ang)));
            s->insertPoint(new Point(r*cos(alfa+ang),base,r*sin(alfa+ang)));
            
            r-=reduction;
            r_in -= reduction;
        }
        s->insertPoint(new Point(r*cos(alfa),topo,r*sin(alfa)));
        s->insertPoint(new Point(0,height,0));
        s->insertPoint(new Point(r*cos(alfa+ang),topo,r*sin(alfa+ang)));
    }
    return s;
}

