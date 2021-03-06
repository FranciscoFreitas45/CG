#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstring>
#include "Action.h"

Action::Action(){
    this->x=0;
    this->y=0;
    this->z=0;
    this->tag="";
}

Rotate::Rotate() {
    this->tag="";
    this->z=0;
    this->x=0;
    this->y=0;
    this->angle=0;
}

float Action::getX() const {
    return x;
}

float Rotate::getAngle() const {
    return angle;
}

void Rotate::setAngle(float angle) {
    Rotate::angle = angle;
}

void Action::setX(float x) {
    Action::x = x;
}

float Action::getY() const {
    return y;
}

void Action::setY(float y) {
    Action::y = y;
}

float Action::getZ() const {
    return z;
}

void Action::setZ(float z) {
    Action::z = z;
}

const string &Action::getTag() const {
    return tag;
}

void Action::setTag(const string &tag) {
    Action::tag = tag;
}


void Action::apply(){
   if(tag == "translate"){
       glTranslatef(x,y,z);
   }
   else if(tag == "scale") {
       glScalef(x, y, z);
   }
   else if(tag == "colour"){
       float rx = x/255;
       float gy = y/255;
       float bz = z/255;
       glColor3f(rx,gy,bz);
   }
}


void  Rotate::apply() {
    glRotatef(angle,x,y,z);
}


Type::Type() {
    this->type="";
}

void Type::setType(const string &type) {
    Type::type=type;
}

void Type::apply(int *linha) {
    if(type == "P"){
    *linha=GL_POINT;

    }
    else if(type == "L"){
        *linha=GL_LINE;
    }

    else if(type == "F"){
        *linha=GL_FILL;
    }
}