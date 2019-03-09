#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include "tinyxml2.h"
#include "../src/Point.h"
#include "../src/Shape.h"


using namespace tinyxml2;
using namespace std;


vector<Point> model;
int linha = GL_LINE;
float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 10;


void readFile(char* FILENAME) {
    vector<string> tokens;
    ifstream file(FILENAME);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
               Point p = Point(line);
               model.push_back(p);
        }
        file.close();
    }
   else {
        printf("NAO ABRIU O FICHEIRO\n");
    }
}

void readXML(char * path){
    XMLDocument doc;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(path);// path2
    if(!eResult){
        element = doc.FirstChildElement()->FirstChildElement(); //<scene><model>
        for (; element; element = element->NextSiblingElement()) { // itera por os model
                string ficheiro = element->Attribute("file"); // pega no valor do atributo file  em cada  Model
                char * aux = const_cast<char *>(ficheiro.c_str());
                readFile(aux); // Gets model's vertexes
        }
    }
    else {
        cout << "o ficheiro nao foi carregado" << endl;
    }
}



void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(rad*cos(beta),rad*sin(beta),rad*cos(beta)*sin(alpha),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT,linha);


    glColor3f(1,1,1);
    for(int i = 0;i<model.size();i+=3){
        glBegin(GL_TRIANGLES);
        glVertex3f(model[i].getX(),model[i].getY(),model[i].getZ());
        glVertex3f(model[i+1].getX(),model[i+1].getY(),model[i+1].getZ());
        glVertex3f(model[i+2].getX(),model[i+2].getY(),model[i+2].getZ());
        glEnd();
    }
    // End of frame
    glutSwapBuffers();
}



void processKeys(unsigned char c, int xx, int yy) {
    switch (c) {
        case 'p':
            linha=GL_POINT;
            break;
        case 'l':
            linha=GL_LINE;
            break;
        case 'f':
            linha=GL_FILL;
            break;
        case '+':
            glPolygonMode(GL_FRONT,GL_POINT);
            rad -= 1;
            glutPostRedisplay();
            break;
        case '-':
            rad += 1;
            glutPostRedisplay();
            break;
        default:
            break;
    }

}


void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            alpha += M_PI / 16;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            alpha -= M_PI / 16;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            beta += M_PI / 16;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            beta -= M_PI / 16;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

//Engine Guide
void printHelp(){
    std::cout << "----------------------------ENGINE_HELP-------------------------------" << std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "GUIDELINE: ./engine <XML FILE>                                        " <<std::endl;
    std::cout << "                     [-h]                                             " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "  FILE:                                                               " <<std::endl;
    std::cout << "Specify the path to a XML file in which the information about the     " <<std::endl;
    std::cout << "models you wish to create are specified                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "  MOVE:                                                               " <<std::endl;
    std::cout << "- RIGHT_ARROW_KEY :                                                   " <<std::endl;
    std::cout << "             Rotate the camera to right                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- LEFT_ARROW_KEY :                                                    " <<std::endl;
    std::cout << "             Rotate the camera to left                                " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- DOWN_ARROW_KEY :                                                    " <<std::endl;
    std::cout << "             Rotate the camera up ( Y Axe - Positive Direction )      " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- UP_ARROW_KEY :                                                      " <<std::endl;
    std::cout << "             Rotate the camera down ( Y Axe - Negative Direction)     " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "  ZOOM:                                                               " <<std::endl;
    std::cout << "- + :                                                                 " <<std::endl;
    std::cout << "      Zoom in                                                         " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "- - :                                                                 " <<std::endl;
    std::cout << "      Zoom out                                                        " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "  FORMAT                                                               " <<std::endl;
    std::cout << "- l :                                                                 " <<std::endl;
    std::cout << "     Figure format into lines                                         " <<std::endl;
    std::cout << "- p :                                                                 " <<std::endl;
    std::cout << "     Figure format into points                                        " <<std::endl;
    std::cout << "- f :                                                                 " <<std::endl;
    std::cout << "     Fill up the figure                                               " <<std::endl;
    std::cout << "                                                                      " <<std::endl;
    std::cout << "----------------------------------END---------------------------------" <<std::endl;
}





int main(int argc, char * argv[]) {
        if(argc<2){
            return 0;
        }

        if(!strcmp(argv[1],"-h")){
            printHelp();
            return 0;
        }

    Shape s= Shape();

            readXML(argv[1]);
            // put GLUT init here
            glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
            glutInitWindowPosition(100,100);
            glutInitWindowSize(800,800);
            glutCreateWindow("CG@DI");
            glClearColor(0,0,0,0) ;
            glClear(GL_COLOR_BUFFER_BIT);



// put callback registration here
            glutDisplayFunc(renderScene);
            glutReshapeFunc(changeSize);
            glutIdleFunc(renderScene);
            glutKeyboardFunc(processKeys);
            glutSpecialFunc(processSpecialKeys);



// OpenGL settings
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
          //  glClearColor(0.0f,0.0f,0.0f,0.0f);

// enter GLUT's main loop
            glutMainLoop();






        }

