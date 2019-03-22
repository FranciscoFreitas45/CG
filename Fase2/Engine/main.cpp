#include <stdlib.h>
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
#include "../src/Group.h"
#include "../src/Action.h"

using namespace tinyxml2;
using namespace std;


Group*scene =new Group(); //Podemos pensar na nossa "scene" como um grupo grande, em que dentro tem mais groups, shapes e ações a acontecer.
int linha = GL_LINE;
float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 10;
int tam=0;

// Parser que identifica o ficheiro relativo ao modelo que se pretende desenhar, e insere os pontos
// na estrutura Shape
Shape* readFile(char* FILENAME ) {
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

// Função auxiliar para o parseGroup. Sempre que há uma ocorrência de group, cria-se
Group* child(Group *g){
    Group *child = new Group(tam++);
    g->addGroup(child);
    std::cout << tam << std::endl;
    return child;
}

// Parser que pega no elemento xml Translate, e guarda as coordenadas que aparecem na lista de actions
// (uma action, como se pode ver no ficheiro Action.h, pode ser um conjunto de 3 floats (coordenadas), ou
// então 3 coordenadas e 1 float (ângulo, no caso do rotate).
void parserTranslate(XMLElement * current,Group *g) {
    float y;
    float x;
    float z;
    Action *action= new Action();
    current->QueryFloatAttribute("X",&x);
    current->QueryFloatAttribute("Y",&x);
    current->QueryFloatAttribute("Z",&z);
    action->setX(x);
    action->setY(y);
    action->setZ(z);
    action->setTag("translate");
    g->addAction(action);
}

// Parser que pega no elemento xml Rotate, e guarda as coordenadas que aparecem na lista de actions
void parserRotate(XMLElement * current,Group *g) {
    float y;
    float x;
    float z;
    float angle;
    Rotate *action= new Rotate();
    current->QueryFloatAttribute("X",&x);
    current->QueryFloatAttribute("Y",&x);
    current->QueryFloatAttribute("Z",&z);
    current->QueryFloatAttribute("angle",&angle);
    action->setX(x);
    action->setY(y);
    action->setZ(z);
    action->setAngle(angle);
    action->setTag("rotate");
    g->addAction(action);

}

// Parser que pega no elemento xml Scale, e guarda as coordenadas que aparecem na lista de actions
void parserScale(XMLElement * current,Group *g) {
    float y;
    float x;
    float z;
    Action *action= new Action();
    current->QueryFloatAttribute("X",&x);
    current->QueryFloatAttribute("Y",&x);
    current->QueryFloatAttribute("Z",&z);
    action->setX(x);
    action->setY(y);
    action->setZ(z);
    action->setTag("scale");
    g->addAction(action);
}

// Parser que pega no elemento xml Translate, e guarda os números das cores que aparecem na lista de actions
void parserColour(XMLElement * current,Group *gr) {
    float r;
    float g;
    float b;
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

// Parser específico para o elemento Models, percorre todos os "Model" e chama a funçao "readFile" que
// armazena na estrutura Shape as suas coordenadas, e depois adiciona-a à lista de models do grupo
void parserModels(XMLElement * current,Group *g){
    vector<Shape*>models;
    XMLElement * element = current->FirstChildElement(); //<model>
    for (; element; element = element->NextSiblingElement()) { // itera por os model
        string ficheiro = element->Attribute("file"); // pega no valor do atributo file  em cada  Model
        char *aux = const_cast<char *>(ficheiro.c_str());
        Shape* shape =readFile(aux); // Gets model's vertexes
        models.push_back(shape);
    }
    g->addShape(models);
}

// PARSER GERAL. Onde as funções acima são chamadas.
void parseGroup(XMLElement * current,Group *g){
    XMLElement* group = current;
    if(!(strcmp(current->Name(),"translate"))) {
        parserTranslate(current,g);
    }
    else if(!(strcmp(current->Name(),"rotate"))) {
        parserRotate(current, g);
    }
    else if(!(strcmp(current->Name(),"scale"))) {
        parserScale(current, g);
    }
    else if(!(strcmp(current->Name(),"models"))) {
        parserModels(current,g);
    }
    else if(!(strcmp(current->Name(),"colour"))) {
        parserColour(current,g);
    }
     else if (!(strcmp(current->Name(), "group"))) { // Caso em que se trata de um group FILHO.
        // Aqui cria-se um novo objeto Group e adiciona-se a lista de filhos do grupo atual.
        // A funçao child devolve o novo Filho para se fazer o parse dentro dele atraves da
         // chamada recursiva de parseGroup
        Group* c = child(g);
        current = current->FirstChildElement();
        if(current)
            parseGroup(current,c);
    }
    group = group->NextSiblingElement(); //quando não se entra em mais nenhum caso, passa-se ao elemento irmão
    if(group) parseGroup(group,g);
}







void readXML(char * path) {
    XMLDocument doc;
    XMLElement *element;
    tinyxml2::XMLError eResult = doc.LoadFile(path);
    if (!eResult) {
        element = doc.FirstChildElement()->FirstChildElement();//<scene><group>
        std::cout << element->Name() << " pai" << std::endl;
        parseGroup(element,scene);
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

/*
    glColor3f(1,1,1);
    for(int i = 0;i<model.size();i+=3){
        glBegin(GL_TRIANGLES);
        glVertex3f(model[i].getX(),model[i].getY(),model[i].getZ());
        glVertex3f(model[i+1].getX(),model[i+1].getY(),model[i+1].getZ());
        glVertex3f(model[i+2].getX(),model[i+2].getY(),model[i+2].getZ());
        glEnd();
    }
    */
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

