#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "Shape.h"
#include <vector>
#include <cstdlib>


using namespace std;


void Shape::insertPoint(Point* p){
    this->points.push_back(p);
}

void Shape::insertNormal(Point* p){
    this->normal.push_back(p);
}

Point* Shape::getPoint(int i) {
    return this->points.at(i);
}

Point* Shape::getNormal(int i) {
    return this->normal.at(i);
}

Material* Shape::getMaterial() {
    return this->material;
}

void Shape::setMaterial(Material* m) {
    this->material = m;
}

int Shape::getNormalSize(){
    return this->normal.size();
}

int Shape::getSize(){
    return this->points.size();
}

void Shape::vbo() {
    float *vertex = (float *) malloc(sizeof(float) * 3 * this->points.size());
    float *n = (float *) malloc(sizeof(float) * 3 * this->normal.size());
    int index = 0, index2 = 0;

    for (int i = 0; i < this->points.size(); i++) {
        vertex[index] = this->points[i]->getX();
        vertex[index + 1] = this->points[i]->getY();
        vertex[index + 2] = this->points[i]->getZ();
        index += 3;
    }

    if(this->normal.size()){
        for (int i = 0; i < this->normal.size(); i++) {
            n[index2] = this->normal[i]->getX();
            n[index2 + 1] = this->normal[i]->getY();
            n[index2 + 2] = this->normal[i]->getZ();
            index2 += 3;
        }
        glGenBuffers(1, buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index, vertex, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index2, n, GL_STATIC_DRAW);
    }
    else{
        glGenBuffers(1, buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index, vertex, GL_STATIC_DRAW);
    } 
    free(vertex);
    free(n);
}

void Shape::draw(){
    cout << normal.size() << "batata";
        if(material)
            this->material->draw();
        
            
        glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
        glVertexPointer(3,GL_FLOAT,0, 0);
        cout << normal.size();
        if(normal.size()!=0){
            glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
            glNormalPointer(GL_FLOAT, 0, 0);
        }
    cout << "cenas" << "\n";
        
        glEnable(GL_LIGHTING);
    cout << "cenasbbbb" << "\n";

        glDrawArrays(GL_TRIANGLES, 0, getSize() * 3);
    cout << "cenasaaaa" << "\n";

        glDisable(GL_LIGHTING);
    cout << "cenaddddd" << "\n";

        glBindTexture(GL_TEXTURE_2D, 0);
    cout << "cenawewews" << "\n";

}
