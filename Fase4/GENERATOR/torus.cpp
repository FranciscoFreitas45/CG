#define _USE_MATH_DEFINES
#include <cmath>
#include "torus.h"
#include "../src/Shape.h"
#include <math.h>
#include <vector>

using std::vector;


Shape* torus(float r, float R, int slices, int stacks) {
    Shape *s= new Shape();
    float alfa, c, beta;
    float a = 2*M_PI/slices;
    float b = 2*M_PI/stacks;
    Point *p;

    for(int i=0; i<slices; i++){
        alfa = i * a;

        for(int j=0; j<=stacks; j++){
            beta = j* b;
            p = new Point((R+r*cos(beta))*cos(alfa),r*sin(beta),(R+r*cos(beta))*sin(alfa));
            s->insertPoint(p);
            s->insertNormal(new Point(cos(alfa),r*sin(beta),sin(alfa)));
            s->insertTexture(p->toUV());

            p = new Point((R+r*cos(beta))*cos(alfa+a),r*sin(beta),(R+r*cos(beta))*sin(alfa+a));
            s->insertPoint(p);
            s->insertNormal(new Point(cos(alfa+a),r*sin(beta),sin(alfa+a)));
            s->insertTexture(p->toUV());

            p = new Point((R+r*cos(beta+b))*cos(alfa+a),r*sin(beta+b),(R+r*cos(beta+b))*sin(alfa+a));
            s->insertPoint(p);
            s->insertNormal(new Point(cos(alfa+a),r*sin(beta+b),sin(alfa+a)));
            s->insertTexture(p->toUV());

            p = new Point((R+r*cos(beta))*cos(alfa),r*sin(beta),(R+r*cos(beta))*sin(alfa));
            s->insertPoint(p);
            s->insertNormal(new Point(cos(alfa),r*sin(beta),sin(alfa)));
            s->insertTexture(p->toUV());

            p = new Point((R+r*cos(beta+b))*cos(alfa+a),r*sin(beta+b),(R+r*cos(beta+b))*sin(alfa+a));
            s->insertPoint(p);
            s->insertNormal(new Point(cos(alfa+a),r*sin(beta+b),sin(alfa+a)));
            s->insertTexture(p->toUV());

            p = new Point((R+r*cos(beta+b))*cos(alfa),r*sin(beta+b),(R+r*cos(beta+b))*sin(alfa));
            s->insertPoint(p);
            s->insertNormal(new Point(cos(alfa),r*sin(beta+b),sin(alfa)));
            s->insertTexture(p->toUV());

        }
    }
    return s;
}
