#include "Point.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;


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
