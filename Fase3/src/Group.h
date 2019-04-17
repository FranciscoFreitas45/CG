#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include "Shape.h"
#include <vector>
#include "Point.h"
#include "Action.h"

using namespace std;


class Group {

private:
    vector <Shape*> models; //Lista de formas
    vector <Action*> actions; //Lista de ações

public:
    Group();
    Group(Group * g);
    void addAction(Action* a);
    void addShape(vector<Shape *>s);
    Group* clone();
    void setModels(const vector<Shape*> &models);
    void setActions(const vector<Action*> &actions);
    vector<Shape*> getModels() ;
    vector<Action*> getActions() ;
};


#endif //GENERATOR_GROUP_H
