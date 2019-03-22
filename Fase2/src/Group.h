//
// Created by cyborg on 21-03-2019.
//

#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H



#include "Shape.h"
#include <vector>
#include "Point.h"
#include "Action.h"


using namespace std;



class Group {

private:
    int id;
    vector <Group*> groups;
    vector <Shape*> models;
    vector<Action*> actions;

public:
    Group();
    Group(int id);
    void addAction(Action* a);
    void addShape(vector<Shape *>s);
    void addGroup(Group* g);
    int size();
};


#endif //GENERATOR_GROUP_H
