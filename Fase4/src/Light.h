#ifndef GENERATOR_LIGHT_H
#define GENERATOR_LIGHT_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
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
