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
