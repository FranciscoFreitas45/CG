#include "Point.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

Point* Point::crossProduct(Point* a, Point* b) {
    float cx, cy, cz;
    cx = a->y * b->z + a->z * b->y;
    cy = a->z * b->x + a->x * b->z;
    cz = a->x * b->y + a->y * b->x;
    return new Point(cx,cy,cz);
}


Point* Point::normalize() {
    float ax = this->x, ay = this->y, az = this->z;
    float magnitude = sqrt((ax*ax) + (ay*ay) + (az*az));
    return new Point(ax/magnitude,ay/magnitude,az/magnitude);
}

float* Point::toUV() {
    float ax = this->x, ay = this->y, az = this->z;
    float* uv = (float *)malloc(2*sizeof(float));
    uv[0] = 0.5+(atan2(az,ax)/2*M_PI);
    uv[1] = 0.5-(asin(ay)/M_PI);
    cout << uv[0] << " ,,, " << uv[1] << " ... " << 0.5-(asin(ay)/M_PI) << "\n";
    return uv;
}


Point::Point(float x, float y, float z){
        this->x=x;
        this->y=y;
        this->z=z;
}

Point::Point(string line){
    vector<string> tokens;
    stringstream check1(line);
    string intermediate;
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    this->x=atof(tokens[0].c_str());
    this->y=atof(tokens[1].c_str());
    this->z=atof(tokens[2].c_str());
}


float Point::getX() {
    return this->x;
}


float Point::getY() {
    return this->y;
}

float Point::getZ() {
    return this->z;
}
