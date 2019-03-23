#include "Point.h"
#include "Group.h"
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
}

void Group::addAction(Action *a) {
    this->actions.push_back(a);
}

void Group::addShape(vector<Shape*>s) { 
    for(int i=0; i<s.size(); i++)
       this->models.push_back(s.at(i));
}


const vector<Action *> &Group::getActions() const {
    return actions;
}

const vector<Shape *> &Group::getModels() const {
    return models;
}

void Group::setActions(const vector<Action*> &actions) {
    Group::actions = actions;
}

void Group::setModels(const vector<Shape*> &models) {
    Group::models = models;
}

Group* Group::clone(){
    return new Group(this);
}








