

#include "Shape.h"
#include <vector>

using namespace std;


void Shape::insertPoint(Point* p){
        this->Points.push_back(p);

}

Point* Shape::getPoint(int i) {
    return this->Points.at(i);
}

int Shape::getSize(){
    return this->Points.size();
}

