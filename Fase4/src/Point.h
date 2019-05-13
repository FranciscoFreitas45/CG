
#ifndef ENGINE_POINT_H
#define ENGINE_POINT_H


#include <cmath>
#include <string>

using  namespace std;
class Point {
private :
    float x;
    float y;
    float z;

public:
    Point();
    Point(float x, float y,float z);
    Point(string line);
    Point* normalize();
    Point* crossProduct(Point*,Point*);
    Point* toUV();
    float getX();
    float getY();
    float getZ();
};

#endif //ENGINE_POINT_H
