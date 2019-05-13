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
#include "tinyxml2.h"
#include "../src/Point.h"
#include "../src/Shape.h"
#include "../src/Group.h"
#include "../src/Action.h"

using namespace tinyxml2;
using namespace std;


vector<Group*> scene;
int linha = GL_LINE;
float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 50;
float px = 0.0;
float py;
float pz = 0.0;
float lx = 0.0;
float ly = 0.0;
float lz = 0.0;
int tam=0;
float cam_angle = 0.0;
float speed=2;
int startX, startY, tracking = 0;


Shape* readFile(char* FILENAME) {
    Shape *s = new Shape();
    ifstream file(FILENAME);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            Point *p = new Point(line);
            s->insertPoint(p);
        }
        file.close();
    }
    else {
        printf("NAO ABRIU O FICHEIRO\n");
    }
    return s;
}


Group* child(Group *g){
    Group *child = g->clone();
    return child;
}


void parseType(XMLElement *current,Group *g ){
    Type *t = new Type();
    const char* tipo=(char*)malloc(sizeof(char)*10);
    current->QueryStringAttribute("type",&tipo);
    string str(tipo);
    //printf(tipo);
    t->setType(tipo);
    g->addAction(t);
}


void parserTranslate(XMLElement * current,Group *g) {
    float y = 0;
    float x = 0;
    float z = 0;
    float time = 0;
    Translate *action= new Translate();
    current->QueryFloatAttribute("time",&time);
    current->QueryFloatAttribute("X",&x);
    current->QueryFloatAttribute("Y",&y);
    current->QueryFloatAttribute("Z",&z);
    action->setX(x);
    action->setY(y);
    action->setZ(z);
    action->setTag("translate");
    action->setTime(time);

    XMLElement* current2 = current->FirstChildElement();

    for (; current2; current2 = current2->NextSiblingElement()){
        float x1 = 0,y1 = 0,z1 = 0;
        current2->QueryFloatAttribute("X",&x1);
        current2->QueryFloatAttribute("Y",&y1);
        current2->QueryFloatAttribute("Z",&z1);
        Point *p = new Point(x1,y1,z1);
        action->addPoint(p);
    }
    g->addAction(action);
}


void parserRotate(XMLElement * current,Group *g) {
    float y = 0;
    float x = 0;
    float z = 0;
    float angle = 0;
    float time = 0;
    Rotate *action= new Rotate();
    current->QueryFloatAttribute("time",&time);
    current->QueryFloatAttribute("X",&x);
    current->QueryFloatAttribute("Y",&y);
    current->QueryFloatAttribute("Z",&z);
    current->QueryFloatAttribute("angle",&angle);
    action->setX(x);
    action->setY(y);
    action->setZ(z);
    action->setAngle(angle);
    action->setTag("rotate");
    action->setTime(time);
    g->addAction(action);
}


void parserScale(XMLElement * current,Group *g) {
    float y = 0;
    float x = 0;
    float z = 0;
    Action *action= new Action();
    current->QueryFloatAttribute("X",&x);
    current->QueryFloatAttribute("Y",&y);
    current->QueryFloatAttribute("Z",&z);
    action->setX(x);
    action->setY(y);
    action->setZ(z);
    action->setTag("scale");
    g->addAction(action);
}


void parserColour(XMLElement * current,Group *gr) {
    float r = 0;
    float g = 0;
    float b = 0;
    Action *action= new Action();
    current->QueryFloatAttribute("R",&r);
    current->QueryFloatAttribute("G",&g);
    current->QueryFloatAttribute("B",&b);
    action->setX(r);
    action->setY(g);
    action->setZ(b);
    action->setTag("colour");
    gr->addAction(action);
}


void parserModels(XMLElement * current,Group *g){
    vector<Shape*>models;
    XMLElement * element = current->FirstChildElement();
    for (; element; element = element->NextSiblingElement()) {
        string ficheiro = element->Attribute("file");
        char *aux = const_cast<char *>(ficheiro.c_str());
        Shape* shape = readFile(aux);
        models.push_back(shape);
    }
    g->addShape(models);
    Group* newGroup = g->clone();
    scene.push_back(newGroup);
}


void parseGroup(XMLElement * current2,Group *g, int level){
    XMLElement* group = current2; //group
    XMLElement* current = current2->FirstChildElement(); //<group></>
    for(; current; current = current->NextSiblingElement()){
        string a = current->Name();
        if(a.compare("translate")==0) {
            parserTranslate(current,g);
        }
        else if(a.compare("rotate")==0) {
            parserRotate(current, g);
        }
        else if(a.compare("scale")==0) {
            parserScale(current, g);
        }
        else if(a.compare("models")==0) {
            parserModels(current,g);
        }
        else if(a.compare("colour")==0) {
            parserColour(current,g);
        }
        else if(a.compare("tag")==0){
            parseType(current,g);
        }
        else if (a.compare("group")==0) {
            Group* c = child(g);
            parseGroup(current,c,2);
        }
    }

    current2 = current2->NextSiblingElement();
    for(; current2 && level==1; current2 = current2->NextSiblingElement()){
        Group* newGroup = new Group();
        parseGroup(current2,newGroup,2);
    }
}







void readXML(char * path) {
    XMLDocument doc;
    XMLElement *element;
    Group* p = new Group();
    tinyxml2::XMLError eResult = doc.LoadFile(path);
    if (!eResult) {
        element = doc.FirstChildElement()->FirstChildElement();//<scene><group>
        parseGroup(element,p,1);
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

void renderGroup(Group* g){
    glPushMatrix();
    vector<Action*> actions = g->getActions();
    for(int i = 0; i < actions.size(); i++){
        Action* act = actions.at(i);
        if (Type* t = dynamic_cast<Type*>(act)){
            t->apply(&linha);
            glPolygonMode(GL_FRONT,linha);
        }
       else {
            act->apply();
        }
    }
    vector<Shape*> models = g->getModels();
    for(int k = 0; k < models.size(); k++){
            models[k]->draw();

        }

    glPopMatrix();
}



void passTovbo(){
    for(int i=0;i<scene.size();i++){
        vector<Shape*> models = scene[i]->getModels();
        for(int j=0;j<models.size();j++)
            models[j]->vbo();
    }
}





void movement_mouse (int button, int state, int x, int y){
    switch(button)
        case GLUT_LEFT_BUTTON:
            alpha -= M_PI / 16;
    glutPostRedisplay();
}



void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lx = px + sin(cam_angle);
    lz = pz + cos(cam_angle);
    // set the camera
    glLoadIdentity();
    gluLookAt(px,py,pz,
              lx,py,lz,
              0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT,linha);


    for(int i = 0; i < scene.size(); i++){
        renderGroup(scene.at(i));
    }

    // End of frame
    glutSwapBuffers();
}
ss


void processKeys(unsigned char key, int xx, int yy) {
    float dx, dy = 0, dz, rx, ry, rz;
    float upx = 0, upy = 1, upz = 0;
    switch (key) {
        case 'w': {
            dx = lx - px;
            dz = lz - pz;
            px = px + speed * dx;
            pz = pz + speed * dz;

            break;
        }
        case 's': {
            dx = lx - px;
            dz = lz - pz;
            px = px + (-speed) * dx;
            pz = pz + (-speed) * dz;

            break;
        }
        case 'e': {
            cam_angle -= 0.1;
            break;
        }
        case 'q': {
            cam_angle += 0.1;
            break;
        }
        case 'a': {
            dx = lx - px;
            dz = lz - pz;
            rx = dy * upz - dz * upy;
            rz = dx * upy - dy * upx;
            px = px + (-speed) * rx;
            pz = pz + (-speed) * rz;

            break;
        }
        case 'd': {
            dx = lx - px;
            dz = lz - pz;
            rx = dy * upz - dz * upy;
            rz = dx * upy - dy * upx;
            px = px + speed * rx;
            pz = pz + speed * rz;

            break;
        }
    }

}
    void processMouseButtons(int button, int state, int xx, int yy) {

        if (state == GLUT_DOWN)  {
            startX = xx;
            startY = yy;
            if (button == GLUT_LEFT_BUTTON)
                tracking = 1;
            else if (button == GLUT_RIGHT_BUTTON)
                tracking = 2;
            else
                tracking = 0;
        }
        else if (state == GLUT_UP) {
            if (tracking == 1) {
                alpha += (xx - startX);
                beta += (yy - startY);
            }
            else if (tracking == 2) {

                rad -= yy - startY;
                if (rad < 3)
                    rad = 3.0;
            }
            tracking = 0;
        }
    }





void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = rad;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = rad - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    px = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    pz = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    py = rAux * 							     sin(betaAux * 3.14 / 180.0);
}
/*

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
*/

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

    Shape s = Shape();

    readXML(argv[1]);

    // put GLUT init here
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI");
    glClearColor(0,0,0,0) ;
    glClear(GL_COLOR_BUFFER_BIT);
    #ifndef __APPLE__
    // init GLEW
    glewInit();
    #endif

    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    //glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);


    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_CULL_FACE);

    passTovbo();

    // enter GLUT's main loop
    glutMainLoop();
}
