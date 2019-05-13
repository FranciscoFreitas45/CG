#include "Shape.h"



using namespace std;


void Shape::insertPoint(Point* p){
    this->points.push_back(p);
}

void Shape::insertNormal(Point* p){
    this->normal.push_back(p);
}

void Shape::insertTexture(Point* uv){
    this->texture.push_back(uv);
}

void Shape::setTexID(GLuint t){
    this->texID = t;
}

Point* Shape::getPoint(int i) {
    return this->points.at(i);
}

Point* Shape::getNormal(int i) {
    return this->normal.at(i);
}

Point* Shape::getTexture(int i) {
    return this->texture.at(i);
}

Material* Shape::getMaterial() {
    return this->material;
}

void Shape::setMaterial(Material* m) {
    this->material = m;
}

int Shape::getNormalSize(){
    return this->normal.size();
}

int Shape::getTextureSize(){
    return this->texture.size();
}

int Shape::getSize(){
    return this->points.size();
}

void Shape::vbo() {
    float *vertex = (float *) malloc(sizeof(float) * 3 * this->points.size());
    float *n = (float *) malloc(sizeof(float) * 3 * this->normal.size());
    float *t = (float *) malloc(sizeof(float) * 2 * this->texture.size());
    int index = 0, index2 = 0, index3 = 0;

    for (int i = 0; i < this->points.size(); i++) {
        vertex[index] = this->points[i]->getX();
        vertex[index + 1] = this->points[i]->getY();
        vertex[index + 2] = this->points[i]->getZ();
        index += 3;
    }

    for (int i = 0; i < this->normal.size(); i++) {
        n[index2] = this->normal[i]->getX();
        n[index2 + 1] = this->normal[i]->getY();
        n[index2 + 2] = this->normal[i]->getZ();
        index2 += 3;
    }

    for (int i = 0; i < this->texture.size(); i++) {
        t[index3] = this->texture[i]->getX();
        t[index3 + 1] = this->texture[i]->getY();
        index3 += 2;
    }

    glGenBuffers(1, &vertices);
	glBindBuffer(GL_ARRAY_BUFFER,vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index * 3, vertex,     GL_STATIC_DRAW);

	glGenBuffers(1, &normals);
	glBindBuffer(GL_ARRAY_BUFFER,normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index2 * 3, n,     GL_STATIC_DRAW);

	glGenBuffers(1, &textures);
	glBindBuffer(GL_ARRAY_BUFFER,textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * index3 * 2, t,     GL_STATIC_DRAW);

    free(vertex);
    free(n);
    free(t);
}

void Shape::loadTexture(string path) {
    unsigned int tw,th, t;
    unsigned char *texData;
    ILuint img;
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &img);
    ilBindImage(img);
    if(! ilLoadImage((ILstring) path.c_str()))
                cout << "Erro a ler imagem :'(\n";

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Shape::draw(){
    if(material)
        this->material->draw();
          
    glBindBuffer(GL_ARRAY_BUFFER,vertices);
    glVertexPointer(3,GL_FLOAT,0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER,normals);
	glNormalPointer(GL_FLOAT,0,0);

	glBindBuffer(GL_ARRAY_BUFFER,textures);
    glTexCoordPointer(2,GL_FLOAT,0,0);
    
    glBindTexture(GL_TEXTURE_2D, texID);
    glDrawArrays(GL_TRIANGLES, 0, getSize() * 3);
    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, 0);
}
