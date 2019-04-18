#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "Light.h"

Light::Light(){
}

Light::Light(bool t, Point* p){
    this->type = t;
    this->point = p;
}

bool Light::getType(){
    return type;
}

Point* Light::getPoint(){
    return point;
}

void Light::setType(bool t){
    this->type = t;
}

void Light::setPoint(Point * p){
    this->point = p;
}

void Light::draw(){

	GLfloat amb[4] = {0.1,0.1,0.1, 1};
	GLfloat diff[4] = {1, 1, 1, 0};
	GLfloat pos[4] = {point->getX(), point->getY() , point->getZ(), (float) this->type};

	// POSICAO DA LUZ
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	
	// COLORAÇÃO DA LUZ
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
}
