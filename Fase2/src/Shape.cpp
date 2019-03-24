

#include "Shape.h"
#include <vector>
#include <cstdlib>



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

/*void Shape::vectorToArray(){
    int i,j=0;
    int size=this->Points.size();
    float * points = (float * ) malloc(sizeof(float)* size *3);

    for(i;i<size;i++){
        points[j++]=this->Points[i]->getX();
        points[j++]=this->Points[i]->getY();
        points[j++]=this->Points[i]->getZ();
    }


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,j*sizeof(float),points, GL_STATIC_DRAW);


}
*/
