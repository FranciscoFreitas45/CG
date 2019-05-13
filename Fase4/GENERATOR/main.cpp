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
#include <string.h>
#include "../src/Point.h"
#include "../src/Shape.h"
#include "bezier.h"
#include "box.h"
#include "cone.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"
#include "torus.h"


void write_shape(Shape* s, char* file_path){
    char buff[1024];
    char path[1024];
    int i;
    int size = s->getSize();
    Point* p;
    Point* uv;

    system("mkdir -p ../files3d/ ");
    strcpy(path,"../files3d/");
    strcat(path,file_path);
    ofstream file (path,std::ofstream::out);
    
    sprintf(buff, "%d\n", size);
    file << buff;
    for(i=0;i<size;i++){
        p= s->getPoint(i);
        sprintf(buff, "%f %f %f\n", p->getX(), p->getY(), p->getZ());
        file << buff;
    }
    
    size = s->getNormalSize();
    if(size > 0){
    sprintf(buff, "%d\n", size);
    file << buff;
    for(i=0;i<size;i++){
        p= s->getNormal(i);
        sprintf(buff, "%f %f %f\n", p->getX(), p->getY(), p->getZ());
        file << buff;
    }}

    size = s->getTextureSize();
    if(size > 0){
    sprintf(buff, "%d\n", size);
    file << buff;
    for(i=0;i<size;i++){
        uv= s->getTexture(i);
        sprintf(buff, "%f %f\n", uv->getX(), uv->getY());
        file << buff;
    }}
    file.close();
}


void generate_plane(char* size, char* file_path){
    float s = atof(size);
    Shape* shape = plane(s);
    write_shape(shape,file_path);
}


void generate_box(char* height, char* width, char* length, char* div, char* file_path){
    float h,w,l;
    int d;
    h = atof(height);
    w = atof(width);
    l = atof(length);
    d = atoi(div);
    Shape* shape = box(h,w,l,d);
    write_shape(shape,file_path);
}

void generate_sphere(char* radius, char* slices, char* stacks, char* file_path){
    float r;
    int s,st;
    r = atof(radius);
    s = atoi(slices);
    st = atoi(stacks);
    Shape* shape = sphere(r,s,st);
    write_shape(shape,file_path);
}

void generate_cone(char* radius, char* height, char* slices, char* stacks, char* file_path){
    float r, h;
    int s,st;
    r = atof(radius);
    h = atof(height);
    s = atoi(slices);
    st = atoi(stacks);
    Shape* shape = cone(r,h,s,st);
    write_shape(shape,file_path);
}


void generate_cylinder(char* radius, char* height, char* slices, char* stacks, char* file_path){
    float r, h;
    int s,st;
    r = atof(radius);
    h = atof(height);
    s = atoi(slices);
    st = atoi(stacks);
    Shape* shape = cylinder(r,h,s,st);
    write_shape(shape,file_path);
}

void generate_torus(char* r,char* R,char* slices,char * stacks,char * file_path){
    float m,M;
    int s,st;
    m=atof(r);
    M=atof(R);
    s=atoi(slices);
    st=atoi(stacks);
    Shape * shape=torus(m,M,s,st);
    write_shape(shape,file_path);
}

void generate_patch(char* t, char * file_orig, char * file_dest){
    float m;
    m=atof(t);
    Shape *shape = parseBezierPatch(m, file_orig);
    write_shape(shape,file_dest);
}


void printHelp(){
    std::cout << "------------------------------HELP------------------------------------" <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "GUIDELINE: ./generator <SHAPE> ... <FILE>                             " <<std::endl;
    std::cout << "                        [-h]                                          " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "  SHAPE:                                                              " <<std::endl;
    std::cout << "- plane <SIZE>                                                        " <<std::endl;
    std::cout << "   Creates a square in the XZ plane with center in origin.            " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- box <HEIGHT> <WIDTH> <LENGTH> <DIVISIONS>                           " <<std::endl;
    std::cout << "   Creates a box with these dimensions and these divisions.           " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- sphere <RADIUS> <SLICE> <STACK>                                     " <<std::endl;
    std::cout << "   Creates a sphere with this radius, this number of slices and this  " <<std::endl;
    std::cout << "   number of stacks.                                                  " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- cone <RADIUS> <HEIGHT> <SLICE> <STACK>                              " <<std::endl;
    std::cout << "   Creates a cone with this base radius, this height, this number of  " <<std::endl;
    std::cout << "   of slices and this number of stacks.                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- cylinder <RADIUS> <HEIGHT> <SLICE> <STACK>                          " <<std::endl;
    std::cout << "   Creates a cylinder with this base radius, this height, this number " <<std::endl;
    std::cout << "   of slices and this number of stacks.                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- torus <RADIUS> <RADIUS> <SLICE> <STACK>                             " <<std::endl;
    std::cout << "  Creates a torus with this minor radius,this major radius,this       " <<std::endl;
    std::cout << "   number of slices and this number of stacks.                        " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- patch <TESSELATION> <INPUT_FILE>                                    " <<std::endl;
    std::cout << "  Creates a teapot with this tesselation, based on this INPUT_FILE.   " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "----------------------------------END---------------------------------" <<std::endl;
}




int main(int argc, char** argv){
    if (argc<2)
            return 0;
    if(!strcmp(argv[1],"-h")) {
        printHelp();
        return 0;
    }
     if(strcmp(argv[1],"plane")==0){
       generate_plane(argv[2],argv[3]);
     }
    if(strcmp(argv[1],"box")==0){
    generate_box(argv[2],argv[3],argv[4],argv[5],argv[6]);
    }
    if(strcmp(argv[1],"sphere")==0){
      generate_sphere(argv[2],argv[3],argv[4],argv[5]);
    }
    if(strcmp(argv[1],"cone")==0){
      generate_cone(argv[2],argv[3],argv[4],argv[5],argv[6]);
     }
    if(strcmp(argv[1],"cylinder")==0){
        generate_cylinder(argv[2],argv[3],argv[4],argv[5],argv[6]);
    }
    if(strcmp(argv[1],"torus")==0){
        generate_torus(argv[2],argv[3],argv[4],argv[5],argv[6]);
    }
    if(strcmp(argv[1],"patch")==0){
        generate_patch(argv[2],argv[3],argv[4]);
    }
    return 1;
}
