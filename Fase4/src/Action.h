#ifndef GENERATOR_ACTION_H
#define GENERATOR_ACTION_H

#include <cmath>
#include <string>
#include <vector>
#include "Point.h"
using namespace std;

class Action {
protected:
    float x;
    float y;
    float z;
    string tag;

public:
    Action();
    virtual void apply();
    float getX() const;
    void setX(float x);
    float getY() const;
    void setY(float y);
    float getZ() const;
    void setZ(float z);
    const string &getTag() const;
    void setTag(const string &tag);

};

class Translate : public Action{
private:
    float time;
    float yzero[3];
    vector <Point*> points; // pontos lidos
    vector <Point*> curvePts; // pontos da curva
public:
    Translate();
    void apply();
    void addPoint(Point*);
    void setTime(float time);
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, vector<Point*> pts);
    vector <Point*> createCurvePoints();
};


class Rotate : public Action{
private:
    float angle;
    float time;
public:
    Rotate();
    float getAngle() const;
    void setAngle(float angle);
    void setTime(float time);
    void apply();

};

class Type : public Action{
private :
    string type;
public:
    Type();
    void apply(int *linha);
    void setType(const string &tag);
};


#endif //GENERATOR_ACTION_H
