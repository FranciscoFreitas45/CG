#include <GL/glew.h>
#include <GL/glut.h>
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

void Shape::vbo() {
    float *vertex = (float *) malloc(sizeof(float) * 3 * this->Points.size());
    int index = 0;
    for (int i = 0; i < this->Points.size(); i++) {
        vertex[index] = this->Points[i]->getX();
        vertex[index + 1] = this->Points[i]->getY();
        vertex[index + 2] = this->Points[i]->getZ();
        index += 3;
    }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index, vertex, GL_STATIC_DRAW);

    free(vertex);
}
    void Shape::draw(){
        glBindBuffer(GL_ARRAY_BUFFER,buffer);
        glVertexPointer(3,GL_FLOAT,0, 0);
        glDrawArrays(GL_TRIANGLES,0,getSize()*3);
    }
