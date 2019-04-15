#ifndef GENERATOR_BEZIER_H
#define GENERATOR_BEZIER_H

#include "../src/Point.h"

vector<string> splitString(string stringInicial, string delimeter);
Point* calcBezierPoint(float *p1, float *p2, float *p3, float *p4, float t);
Point* calcBezierPatch(float **controlpoints, float u, float v, int npatch);
Shape* parseBezierPatch(float tess, char* file_orig);

#endif //GENERATOR_BEZIER_H
