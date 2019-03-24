#include <GL/gl.h>
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
/*z
void Action::apply(){
    char* string = &tag;
    switch(tag){
		case (!strcmp(tag,"translate")):
			glTranslatef(x,y,z);
			break;
		case "scale":
			glScalef(x,y,z);
			break;
		case "colour":
			float rx = x/255;
			float gy = y/255;
			float bz = z/255;
			glColor3f(rx,gy,bz);
    }
}*/


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

void Rotate::apply() {
    glRotatef(angle,x,y,z);
}

