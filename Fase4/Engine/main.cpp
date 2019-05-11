#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "tinyxml2.h"
#include "../src/Point.h"
#include "../src/Shape.h"
#include "../src/Group.h"
#include "../src/Action.h"

using namespace tinyxml2;
using namespace std;

GLfloat amb[4] = {0.2,0.2,0.2,1.0};
GLfloat diff[4] = {1.0,1.0,1.0,1.0};
GLfloat pos[4] = {0.0,3.0,0.0,0.0};


vector<Group*> scene;
int linha = GL_FILL;
float alpha = 0.61547999;
float beta = 0.61547999;
float rad = 70;
int tam=0;



Shape* readFile(char* FILENAME) {
    int i = 0, points = 0, normals = 0, texs = 0;
    Shape *s = new Shape();
    ifstream file(FILENAME);
    if (file.is_open()) {
        std::string line;
        getline(file,line);
        points = atoi(line.c_str());
        while (i < points) {
            getline(file,line);
            Point *p = new Point(line);
            s->insertPoint(p);
            i++;
        }
        i = 0;
        getline(file,line);
        normals = atoi(line.c_str());
        while (i < normals) {
            getline(file,line);
            Point *p = new Point(line);
            s->insertNormal(p);
            i++;
        }
        i = 0;
        int t = 0;
        getline(file,line);
        texs = atoi(line.c_str());
        float* uv = (float*)malloc(texs*2*sizeof(float));
        while (i < texs) {
            getline(file,line);
            vector<string> tokens;
            stringstream check1(line);
            string intermediate;
            while(getline(check1, intermediate, ' ')){
                tokens.push_back(intermediate);
            }
            uv[t] = atof(tokens[0].c_str());
            uv[t+1] = atof(tokens[1].c_str());
            printf("%d %d\n",uv[t],uv[t+1]);
            s->insertTexture(uv+t);
            t+=2;
            i++;
        }
        free(uv);
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
    t->setType(tipo);
    g->addAction(t);
}

void parserLights(XMLElement * current,Group *g) {
    bool type = false;
    float x = 0;
    float y = 0;
    float z = 0;
    char s[12];
    Light* l = new Light();
    current->QueryFloatAttribute("posX",&x);
    current->QueryFloatAttribute("posY",&y);
    current->QueryFloatAttribute("posZ",&z);
    Point* p = new Point(x,y,z);
    l->setPoint(p);
    if(!strcmp(current->Attribute("type"),"POINT"))
        type = true;
    l->setType(type);
    g->addLight(l);
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
    Action* diffuse = NULL;
	Action* ambient = NULL;
	Action* specular = NULL;
    Action* emission = NULL;
    string textureName;
    GLuint textureID;
    float shininess = 0;
    bool isThereMaterial = false, hasTexture = false;
    XMLElement * element = current->FirstChildElement();
    for (; element; element = element->NextSiblingElement()) {
        string ficheiro = element->Attribute("file");
        if(element->Attribute("diffX") || element->Attribute("diffY") || element->Attribute("diffZ")){
            diffuse = new Action();
            diffuse->setTag("colour");
            diffuse->setX(stof(element->Attribute("diffX")));
            diffuse->setY(stof(element->Attribute("diffY")));
            diffuse->setZ(stof(element->Attribute("diffZ")));
            isThereMaterial = true;
        }
        if(element->Attribute("specX") || element->Attribute("specY") || element->Attribute("specZ")){
            specular = new Action();
            specular->setTag("colour");
            specular->setX(stof(element->Attribute("specX")));
            specular->setY(stof(element->Attribute("specY")));
            specular->setZ(stof(element->Attribute("specZ")));
            isThereMaterial = true;
        }
        if(element->Attribute("emiX") || element->Attribute("emiY") || element->Attribute("emiZ")){
            emission = new Action();
            emission->setTag("colour");
            emission->setX(stof(element->Attribute("emiX")));
            emission->setY(stof(element->Attribute("emiY")));
            emission->setZ(stof(element->Attribute("emiZ")));
            isThereMaterial = true;
        }
        if(element->Attribute("ambX") || element->Attribute("ambY") || element->Attribute("ambZ")){
            ambient = new Action();
            ambient->setTag("colour");
            ambient->setX(stof(element->Attribute("ambX")));
            ambient->setY(stof(element->Attribute("ambY")));
            ambient->setZ(stof(element->Attribute("ambZ")));
            isThereMaterial = true;
        }

        if(element->Attribute("shine")){
            shininess = stof(element->Attribute("shine"));
            isThereMaterial = true;
        }
        
        if(element->Attribute("texture")){
            textureName = element->Attribute("texture");
            hasTexture = true;
        }
        char *aux = const_cast<char *>(ficheiro.c_str());
        Shape* shape = readFile(aux);
        if(isThereMaterial){
            Material* m = new Material(diffuse,ambient,specular,emission,shininess); 
            shape->setMaterial(m);
        }
        if(hasTexture){
            shape->loadTexture(textureName);
        }
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

        if(a.compare("lights")==0) {
            parserLights(current,g);
        }
        else if(a.compare("translate")==0) {
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
    
    vector<Light*> lights = g->getLights();
    for(int k = 0; k < lights.size(); k++){
        lights[k]->draw();
    }

    vector<Action*> actions = g->getActions();
    for(int i = 0; i < actions.size(); i++){
        Action* act = actions.at(i);
        if (Type* t = dynamic_cast<Type*>(act)){
            t->apply(&linha);
            glPolygonMode(GL_FRONT_AND_BACK,linha);
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
        for(int j=0;j<models.size();j++){
            models[j]->vbo();
        }
    }
}


void movement_mouse (int button, int state, int x, int y){
    switch(button)
        case GLUT_LEFT_BUTTON:
            alpha -= M_PI / 16;
    glutPostRedisplay();
}


void renderScene(void) {

    float pos[4] = {1.0, 1.0, 1.0, 0.0};
    float fps;
    int time;
    char s[64];
    
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set the camera
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glMaterialf(GL_FRONT, GL_SHININESS,50.0);
    gluLookAt(rad*cos(beta),rad*sin(beta),rad*cos(beta)*sin(alpha),
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT,linha);


    for(int i = 0; i < scene.size(); i++){
        renderGroup(scene.at(i));
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
    Shape s = Shape();
    readXML(argv[1]);
    cout << "cenas\n"<<endl;;
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
    cout << "cenas\n"<<endl;;
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(movement_mouse);
    // OpenGL settings
    cout << "cenas\n"<<endl;;
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    
    cout << "cenas"<<endl;;
    passTovbo();
    cout << "cenas"<<endl;;
    glutMainLoop();
    return 1;
}
