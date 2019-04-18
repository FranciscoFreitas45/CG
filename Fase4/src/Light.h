#ifndef GENERATOR_LIGHT_H
#define GENERATOR_LIGHT_H


#include <GLUT/glut.h>
#include <iostream>

#include "Point.h"

class Light{

	bool type;
	Point* point;

	public:
		Light();
		Light(bool, Point*);
		bool getType();
		Point* getPoint();
		void setType(bool);
		void setPoint(Point*);
		void draw();
};

#endif