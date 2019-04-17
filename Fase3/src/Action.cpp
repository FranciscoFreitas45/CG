#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstring>
#include "Action.h"

Action::Action(){
    this->x=0;
    this->y=0;
    this->z=0;
    this->tag="";
}

Rotate::Rotate() {
    this->tag="";
    this->z=0;
    this->x=0;
    this->y=0;
    this->angle=0;
    this->time=0;
}

Translate::Translate() {
    this->x=0;
    this->y=0;
    this->z=0;
    this->tag="";
    this->time=0;
    this->yzero[0]=0;
    this->yzero[1]=1;
    this->yzero[2]=0;
}

float Action::getX() const {
    return x;
}

float Rotate::getAngle() const {
    return angle;
}

void Rotate::setAngle(float angle) {
    Rotate::angle = angle;
}

void Action::setX(float x) {
    Action::x = x;
}

float Action::getY() const {
    return y;
}

void Action::setY(float y) {
    Action::y = y;
}

float Action::getZ() const {
    return z;
}

void Action::setZ(float z) {
    Action::z = z;
}

const string &Action::getTag() const {
    return tag;
}

void Action::setTag(const string &tag) {
    Action::tag = tag;
}

void Rotate::setTime(float time) {
    Rotate::time = time;
}

void Translate::setTime(float time) {
    Translate::time = time;
}


void Action::apply(){
   if(tag == "scale") {
       glScalef(x, y, z);
   }
   else if(tag == "colour"){
       float rx = x/255;
       float gy = y/255;
       float bz = z/255;
       glColor3f(rx,gy,bz);
   }
}


void Rotate::apply() {
    float aux,ang;
    if (angle != 0){
        glRotatef(angle,x,y,z);
    }
    else {
        aux = glutGet(GLUT_ELAPSED_TIME)%(int)(time*1000);
        ang = ((aux/(time*1000))*360);
        glRotatef(ang,x,y,z);
    }
}

void Translate::addPoint(Point *p) {
    this->points.push_back(p);
}



Type::Type() {
    this->type="";
}

void Type::setType(const string &type) {
    Type::type=type;
}

void Type::apply(int *linha) {
    if(type == "P"){
    *linha=GL_POINT;

    }
    else if(type == "L"){
        *linha=GL_LINE;
    }

    else if(type == "F"){
        *linha=GL_FILL;
    }
}


//CURVA CATMULL

void getCatmullRomPoint(float t, int *indices, float *pos, float *deriv, vector<Point*> pts){
    float t2 = t * t;
    float t3 = t2 *t;
    float posAux[4],derivAux[4];

    Point* p0 = pts[indices[0]];
    Point* p1 = pts[indices[1]];
    Point* p2 = pts[indices[2]];
    Point* p3 = pts[indices[3]];

    float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                      { 1.0f, -2.5f,  2.0f, -0.5f},
                      {-0.5f,  0.0f,  0.5f,  0.0f},
                      { 0.0f,  1.0f,  0.0f,  0.0f}};
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;

    deriv[0] = 0;
    deriv[1] = 0;
    deriv[2] = 0;

    // Compute A = M * P
    posAux[0] = t3*m[0][0] + t2*m[1][0] + t*m[2][0] + m[3][0];
    posAux[1] = t3*m[0][1] + t2*m[1][1] + t*m[2][1] + m[3][1];
    posAux[2] = t3*m[0][2] + t2*m[1][2] + t*m[2][2] + m[3][2];
    posAux[3] = t3*m[0][3] + t2*m[1][3] + t*m[2][3] + m[3][3];

    derivAux[0] = (3*t2)*m[0][0] + (2*t)*m[1][0] + m[2][0];
    derivAux[1] = (3*t2)*m[0][1] + (2*t)*m[1][1] + m[2][1];
    derivAux[2] = (3*t2)*m[0][2] + (2*t)*m[1][2] + m[2][2];
    derivAux[3] = (3*t2)*m[0][3] + (2*t)*m[1][3] + m[2][3];

    // Compute pos = T * A

    pos[0] = posAux[0]*p0->getX()+posAux[1]*p1->getX()+ posAux[2]*p2->getX()+ posAux[3]*p3->getX();
    pos[1] = posAux[0]*p0->getY()+posAux[1]*p1->getY()+ posAux[2]*p2->getY()+ posAux[3]*p3->getY();
    pos[2] = posAux[0]*p0->getZ()+posAux[1]*p1->getZ()+ posAux[2]*p2->getZ()+ posAux[3]*p3->getZ();

    // Compute deriv = T' * A

    deriv[0] = derivAux[0]*p0->getX()+derivAux[1]*p1->getX()+ derivAux[2]*p2->getX()+ derivAux[3]*p3->getX();
    deriv[1] = derivAux[0]*p0->getY()+derivAux[1]*p1->getY()+ derivAux[2]*p2->getY()+ derivAux[3]*p3->getY();
    deriv[2] = derivAux[0]*p0->getZ()+derivAux[1]*p1->getZ()+ derivAux[2]*p2->getZ()+ derivAux[3]*p3->getZ();

}

void Translate::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, vector<Point*> pts){
    int numPontos = pts.size();
    float t = gt * numPontos;
    int index = floor(t);
    t = t - index;

    int indices[4];

    indices[0] = (index + numPontos-1) % numPontos;
    indices[1] = (indices[0]+1) % numPontos;
    indices[2] = (indices[1]+1) % numPontos;
    indices[3] = (indices[2]+1) % numPontos;

    getCatmullRomPoint(t,indices,pos,deriv,pts);

}

vector<Point*> Translate::createCurvePoints(){
    float pos[3], deriv[3];
    float t;

    for(t = 0; t < 1; t+=0.01){
        getGlobalCatmullRomPoint(t,pos,deriv,this->points);
        Point* pt = new Point(pos[0],pos[1],pos[2]);
        this->curvePts.push_back(pt);
    }

    return curvePts;

}

void renderCatmullRomCurve(vector<Point*> cpts) {
    int numPontos = cpts.size();
    float aux[3];

    glBegin(GL_LINE_LOOP);
    for(int i = 0; i<numPontos; i++){
        aux[0] = cpts[i]->getX();
        aux[1] = cpts[i]->getY();
        aux[2] = cpts[i]->getZ();
        glVertex3fv(aux);
    }
    glEnd();

}


void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void rotateCurve(float *deriv, float *y){
    float z[3];

    cross(deriv,y,z);
    cross(z,deriv,y);

    normalize(deriv);
    normalize(y);
    normalize(z);

    float m[4][4];
    buildRotMatrix(deriv,y,z,(float*)m);
    glMultMatrixf((float*)m);
}

void Translate::apply() {
    float gt, aux;
    float pos[3],deriv[3];

    if (time == 0)
        glTranslatef(x,y,z);
    else {
        aux = glutGet(GLUT_ELAPSED_TIME)%(int)(time*1000);
        gt = aux/(time*1000);

        vector<Point*> cpts = createCurvePoints();
        renderCatmullRomCurve(cpts);

        getGlobalCatmullRomPoint(gt,pos,deriv,this->points);
        curvePts.clear();
        glTranslatef(pos[0],pos[1],pos[2]);
        rotateCurve(deriv,this->yzero);
    }
}
