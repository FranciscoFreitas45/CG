#ifndef GENERATOR_MATERIAL_H
#define GENERATOR_MATERIAL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>

#include "Action.h"

class Material{

	float diffuse[4]; 	// default: {1, 1, 1, 1};
	float ambient[4]; 	// default: {0.2, 0.2, 0.2, 1};
	float specular[4]; 	// default: {0, 0, 0, 1};
	float emission[4]; 	// default: {0, 0, 0, 1};
	float shininess; 	// default: 0;

	public:
		Material();
		Material(Action*, Action*, Action*, Action*, float);
		void draw();
};

#endif
