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
    vector <Group*> groups; //Lista de elementos group
    vector <Shape*> models; //Lista de formas
    vector <Action*> actions; //Lista de ações

public:
    Group();
    Group(int id);
    void addAction(Action* a);
    void addShape(vector<Shape *>s);
    void addGroup(Group* g);
    int size();
    vector<Action*> getActions();
    vector<Shape*> getModels();
    vector<Group*> getGroups();
};


#endif //GENERATOR_GROUP_H
