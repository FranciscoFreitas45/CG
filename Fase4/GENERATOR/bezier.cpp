#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include "../src/Point.h"
#include "../src/Shape.h"

using namespace std;
int rr=0;
int indexes[512][16];
int npatches = 0;



vector<string> splitString(string stringInicial, string delimeter){
    vector<string> res;
    int startIndex = 0;
    int  endIndex = 0;
    while((endIndex = stringInicial.find(delimeter, startIndex)) < stringInicial.size()) {
        string val = stringInicial.substr(startIndex, endIndex - startIndex);
        res.push_back(val);
        startIndex = endIndex + delimeter.size();
    }
    if(startIndex < stringInicial.size()) {
        std::string val = stringInicial.substr(startIndex);
        res.push_back(val);
    }
    return res;
}



Point* calcBezierPoint(float *p1, float *p2, float *p3, float *p4, float t){
    float point[3];
    float b0 = (1 - t) * (1 - t) * (1 - t);
    float b1 = 3 * t * (1 - t) * (1 - t);
    float b2 = 3 * t * t * (1 - t);
    float b3 = t * t * t;
    point[0] = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
    point[1] = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
    point[2] = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];
    return (new Point(point[0],point[1],point[2]));
}


Point* calcBezierPatch(float **controlpoints, int npatch, float u, float v){
    float temp[16][3], res[16][3];
    Point *p, *ret;
    int w = 0, j = 0;
    //Obter pontos
    for(int i=0; i<16; i++){
        temp[j][0] = controlpoints[indexes[npatch][i]][0];
        temp[j][1] = controlpoints[indexes[npatch][i]][1];
        temp[j][2] = controlpoints[indexes[npatch][i]][2];

        j++;
        //Quando tivermos 4 pontos, podemos fazer o calculo de Bezier
        if( j % 4 == 0 ){
            p = calcBezierPoint(temp[0],temp[1],temp[2],temp[3],u);
            res[w][0] = p->getX();
            res[w][1] = p->getY();
            res[w][2] = p->getZ();

            w++;

            j = 0;
        }
    }
    ret = calcBezierPoint(res[0],res[1],res[2],res[3],v);
    return ret;
}


Shape* parseBezierPatch(float tess, char* file_orig){
    ifstream in;
    in.open(file_orig);
    int c=0, ncontrolpoints=0;

    if(!in){
        cout << "Couldn't open file!\n" ;
        exit(1);
    }

    Shape* s = new Shape();
    char str[1024*1024];
    in.getline(str,1024*1024);
    int n = atoi(str);
    npatches = n;
    
    //apanha linhas de indices e guarda em arrays com indice igual ao indice da linha
    for(int i=0; i<n; i++){
        in.getline(str,1024*1024);
        vector<string> split = splitString(str, ", ");
        for(int j=0; j<split.size(); j++)
            indexes[i][j] = atoi(split[j].c_str());
    }
    
    // linha com numero de pontos de controlo (basicamente = ao numero de linhas a ler a seguir a esta)
    in.getline(str,1024*1024);
    ncontrolpoints = atoi(str);
    float** controlpoints = new float*[ncontrolpoints];
    
    // ler pontos de controlo
    for(int i=0; i<ncontrolpoints; i++){
        c = 0;
        in.getline(str,1024*1024);
        vector<string> split = splitString(str, ", ");
        controlpoints[i] = new float[3];
        for(int j=0; j<split.size(); j++){
            controlpoints[i][j] = atof(split[j].c_str());
        }
    }
    in.close();


    float u1, v1, u2, v2, inc = 1.0/tess;
    Point* res[npatches][4];
    Point* temp, *normal;

    for(int i=0; i<npatches; i++){
        for(int j=0; j<tess; j++){
            for(int w=0; w<tess; w++){
                u1 = j*inc;
                v1 = w*inc;
                u2 = (j+1)*inc;
                v2 = (w+1)*inc;

                res[i][0] = calcBezierPatch(controlpoints, i, u1, v1);
                res[i][1] = calcBezierPatch(controlpoints, i, u2, v1);
                res[i][2] = calcBezierPatch(controlpoints, i, u1, v2);
                res[i][3] = calcBezierPatch(controlpoints, i, u2,v2);

                //0,1,3
                temp = new Point(res[i][0]->getX(),res[i][0]->getY(),res[i][0]->getZ());
                s->insertPoint(temp);
                normal = temp->normalize();
                s->insertNormal(new Point(normal->getX(),normal->getY(),normal->getZ()));
                temp = new Point(res[i][1]->getX(),res[i][1]->getY(),res[i][1]->getZ());
                s->insertPoint(temp);
                normal = temp->normalize();
                s->insertNormal(new Point(normal->getX(),normal->getY(),normal->getZ()));
                temp = new Point(res[i][3]->getX(),res[i][3]->getY(),res[i][3]->getZ());
                s->insertPoint(temp);
                normal = temp->normalize();
                s->insertNormal(new Point(normal->getX(),normal->getY(),normal->getZ()));
                //0,3,2
                temp = new Point(res[i][0]->getX(),res[i][0]->getY(),res[i][0]->getZ());
                s->insertPoint(temp);
                normal = temp->normalize();
                s->insertNormal(new Point(normal->getX(),normal->getY(),normal->getZ()));
                temp = new Point(res[i][3]->getX(),res[i][3]->getY(),res[i][3]->getZ());
                s->insertPoint(temp);
                normal = temp->normalize();
                s->insertNormal(new Point(normal->getX(),normal->getY(),normal->getZ()));
                temp = new Point(res[i][2]->getX(),res[i][2]->getY(),res[i][2]->getZ());
                s->insertPoint(temp);
                normal = temp->normalize();
                s->insertNormal(new Point(normal->getX(),normal->getY(),normal->getZ()));
            }
        }
    }
    return s;
}
