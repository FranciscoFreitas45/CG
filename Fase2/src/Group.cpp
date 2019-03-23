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

Group::Group(int id){
    this->id = id;
}

void Group::addAction(Action *a) {
    this->actions.push_back(a);
}

void Group::addShape(vector<Shape*>s) { 
    for(int i=0; i<s.size(); i++)
       this->models.push_back(s.at(i));
    //this->models=s;
}

void Group::addGroup(Group* g){
    this->groups.push_back(g);
}

int Group::size(){
    return this->groups.size();
}

vector<Action*> Group::getActions() {
    return actions;
}

vector<Shape*> Group::getModels() {
    return models;
}

vector<Shape*> Group::getGroups() {
    return groups;
}







