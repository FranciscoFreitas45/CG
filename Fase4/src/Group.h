#ifndef GENERATOR_GROUP_H
#define GENERATOR_GROUP_H

#include "Shape.h"
#include <vector>
#include "Point.h"
#include "Action.h"
#include "Light.h"

using namespace std;


class Group {

private:
    vector <Shape*> models; //Lista de formas
    vector <Action*> actions; //Lista de ações
    vector<Light*> lights; //Lista de luzes

public:
    Group();
    Group(Group * g);
    void addAction(Action* a);
    void addLight(Light* l);
    void addShape(vector<Shape *>s);
    Group* clone();
    void setModels(const vector<Shape*> &models);
    void setActions(const vector<Action*> &actions);
    void setLights(const vector<Light*> &lights);
    vector<Shape*> getModels();
    vector<Action*> getActions();
    vector<Light*> getLights();
};


#endif //GENERATOR_GROUP_H
