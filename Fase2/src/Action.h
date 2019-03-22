#ifndef GENERATOR_ACTION_H
#define GENERATOR_ACTION_H

#include <cmath>
#include <string>
using namespace std;

class Action {
protected:
    float x;
    float y;
    float z;
    string tag;

public:
    Action();
    void aplly();

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    const string &getTag() const;

    void setTag(const string &tag);

};

class Rotate : public Action{
private:
    float angle;
public:
    Rotate();

    float getAngle() const;

    void setAngle(float angle);

};



#endif //GENERATOR_ACTION_H
