#define _USE_MATH_DEFINES
#include <cmath>
#include "sphere.h"
#include "../src/Shape.h"


Shape * sphere(float radius, int slices, int stacks) {
    Shape *s = new Shape();
    Point* p;
    float alfa, b,beta_in, beta_out;
    float reduction = M_PI/stacks;
    float r;
    float ang = 2*M_PI/slices;
    for(int i=0; i<slices; i++){
        b = 0.01*i;
        alfa =  i*(M_PI*2/slices);

        beta_in = M_PI/2;
        beta_out = beta_in - reduction;
        r = radius;
        for(int j=1; j<=stacks; j++){
            if(j==1){
                p = new Point(r*cos(alfa)*cos(beta_out),r*sin(beta_out),r*sin(alfa)*cos(beta_out));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(0,r,0);
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa+ang)*cos(beta_out),r*sin(beta_out),r*sin(alfa+ang)*cos(beta_out));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());
                beta_in -= reduction;
                beta_out -= reduction;
            }

            else if(j==stacks){
                p = new Point(0,-r,0);
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa)*cos(beta_in),r*sin(beta_in),r*sin(alfa)*cos(beta_in));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa+ang)*cos(beta_in),r*sin(beta_in),r*sin(alfa+ang)*cos(beta_in));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());
                beta_in -= reduction;
                beta_out -= reduction;
            }

            else{
                p = new Point(r*cos(alfa)*cos(beta_in),r*sin(beta_in),r*sin(alfa)*cos(beta_in));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa+ang)*cos(beta_in),r*sin(beta_in),r*sin(alfa+ang)*cos(beta_in)); 
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa+ang)*cos(beta_out),r*sin(beta_out),r*sin(alfa+ang)*cos(beta_out));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa)*cos(beta_out),r*sin(beta_out),r*sin(alfa)*cos(beta_out));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa)*cos(beta_in),r*sin(beta_in),r*sin(alfa)*cos(beta_in));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                p = new Point(r*cos(alfa+ang)*cos(beta_out),r*sin(beta_out),r*sin(alfa+ang)*cos(beta_out));
                s->insertPoint(p);
                s->insertNormal(p->normalize());
                s->insertTexture(p->toUV());

                beta_in -= reduction;
                beta_out -= reduction;
            }
        }
    }
    return s;
}
