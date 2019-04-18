#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "Material.h"

Material::Material(){
}

Material::Material(Action* diff, Action* amb, Action* spec, Action* emi, float shine){
    diffuse[3] = -1;
	ambient[3] = -1;

	if(diff != NULL){
		diffuse[0] = diff->getX();
		diffuse[1] = diff->getY();
		diffuse[2] = diff->getZ();
		diffuse[3] = 1;
	}

	if(amb != NULL){
		ambient[0] = amb->getX();
		ambient[1] = amb->getY();
		ambient[2] = amb->getZ();
		ambient[3] = 1;
	}

	specular[0] = spec->getX();
	specular[1] = spec->getY();
	specular[2] = spec->getZ();
	specular[3] = 1;

	emission[0] = emi->getX();
	emission[1] = emi->getY();
	emission[2] = emi->getZ();
	emission[3] = 1;

	shininess = shine;
}


void Material::draw(){
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	if(diffuse[3] != -1)
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	if(ambient[3] != -1)
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
