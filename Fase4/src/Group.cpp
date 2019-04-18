#include "Point.h"
#include "Group.h"
#include "Light.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <vector>


using namespace std;

Group::Group(){
}

Group::Group(Group* c){
    this->actions = c->getActions();
    this->models = c->getModels();
    this->lights = c->getLights();
}

void Group::addAction(Action *a) {
    this->actions.push_back(a);
}

void Group::addLight(Light *l) {
    this->lights.push_back(l);
}

void Group::addShape(vector<Shape*>s) {
    for(int i=0; i<s.size(); i++)
       this->models.push_back(s.at(i));
}


vector<Action *> Group::getActions() {
    return actions;
}

vector<Shape *> Group::getModels() {
    return models;
}

vector<Light *> Group::getLights() {
    return lights;
}

void Group::setActions(const vector<Action*> &actions) {
    Group::actions = actions;
}

void Group::setModels(const vector<Shape*> &models) {
    Group::models = models;
}

void Group::setLights(const vector<Light*> &lights) {
    Group::lights = lights;
}

Group* Group::clone(){
    return new Group(this);
}
