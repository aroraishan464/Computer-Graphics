#include<GL/glut.h>
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<vector>

#define PI 3.14159265358
#define DRAWPOLYGON 0
#define TRANSLATE 1
#define ROTATE 2
#define SCALE 3
#define REFLECT 4
#define SHEARING 5
using namespace std;
int tran_x,tran_y;
int _xtmp,_ytmp;
int mode=DRAWPOLYGON;
const int winwidth=800;
const int winheight=640;

struct position{
    double x;
    double y;
};

typedef GLfloat Matrix3x3[3][3];
Matrix3x3 CompositeMat;
vector<position> xy;
position tmp;
void DrawPolygon();
void dragmouse(int x,int y);
void mymouse(int button,int state,int x,int y);

void SetIdentity(Matrix3x3 mat){
    GLint row,col;
    for(row=0;row<3;row++){
        for(col=0;col<3;col++)
            mat[row][col]=(row==col);
    }
}

void init(){
    glClearColor(0.93,0.78,0.68,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,winwidth,winheight,0);
    SetIdentity(CompositeMat);
}

void MultiplyMat(Matrix3x3 m1,Matrix3x3 m2){
    GLint row,col;
    Matrix3x3 tmp;
    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            tmp[row][col]=m1[row][0]*m2[0][col]+m1[row][1]*
                m2[1][col]+m1[row][2]*m2[2][col];
        }
    }

    for(row=0;row<3;row++){
        for(col=0;col<3;col++){
            m2[row][col]=tmp[row][col];
        }
    }
}

void writeOnScreen(float x, float y, float z, char *str) {
  glRasterPos3f(x, y, z);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void writeSmaller(float x, float y, float z, char *str) {
  glRasterPos3f(x, y, z);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
  }
}

void translation(GLfloat tx,GLfloat ty){
    Matrix3x3 matTransl;
    SetIdentity(matTransl);
    matTransl[0][2]=tx;
    matTransl[1][2]=ty;
    MultiplyMat(matTransl,CompositeMat);
}

void rotation(int x,int y,float theta){
    theta=theta/180*PI;
    Matrix3x3 matRot;
    SetIdentity(matRot);
    matRot[0][0]=cos(theta);
    matRot[0][1]=-sin(theta);
    matRot[0][2]=x*(1-cos(theta))+y*sin(theta);
    matRot[1][0]=sin(theta);
    matRot[1][1]=cos(theta);
    matRot[1][2]=y*(1-cos(theta))-x*sin(theta);
    MultiplyMat(matRot,CompositeMat);
}

void scaling(GLfloat sx,GLfloat sy,int x,int y){//Arbitrary
    Matrix3x3 matScale;
    SetIdentity(matScale);
    matScale[0][0]=sx;
    matScale[0][2]=(1-sx)*x;
    matScale[1][1]=sy;
    matScale[1][2]=(1-sy)*y;
    MultiplyMat(matScale,CompositeMat);
}

void reflection(int x)
{
    if(x==120)
    {
        Matrix3x3 matrefl={{1,0,0},{0,-1,winheight},{0,0,1}};
        MultiplyMat(matrefl,CompositeMat);
    }
    if(x==121)
    {
        Matrix3x3 matreflx={{-1,0,winwidth},{0,1,0},{0,0,1}};
        MultiplyMat(matreflx,CompositeMat);
    }
    if(x==122)
    {
        Matrix3x3 matreflx={{-1,0,winwidth},{0,-1,winheight},{0,0,1}};
        MultiplyMat(matreflx,CompositeMat);
    }
}

void Shearing(GLfloat sx,GLfloat sy,int x,int y)
{
    Matrix3x3 matShear ={{1,sx,-sx*y},{sy,1,-sy*x},{0,0,1}};
    MultiplyMat(matShear,CompositeMat);
}

void transformedPoints(){
    GLfloat tmp;
    for(int i=0;i<xy.size();i++)
    {
        tmp=CompositeMat[0][0]*xy[i].x+CompositeMat[0][1]*xy[i].y+CompositeMat[0][2];
        xy[i].y=CompositeMat[1][0]*xy[i].x+CompositeMat[1][1]*xy[i].y+CompositeMat[1][2];
        xy[i].x=tmp;
    }
    glutPostRedisplay();
    SetIdentity(CompositeMat);
}


void DrawPolygon()
{
    glColor3f(0.06,0.29,0.56);
    glBegin(GL_POLYGON);
    for(unsigned int i=0;i<xy.size();i++){
        glVertex2f(xy[i].x,xy[i].y);
    }
    glEnd();
}

void drawSquare()
{
    tmp.x=winwidth/2-30;
    tmp.y=winheight/2-30;
    xy.push_back(tmp);

    tmp.x=winwidth/2+30;
    tmp.y=winheight/2-30;
    xy.push_back(tmp);

    tmp.x=winwidth/2+30;
    tmp.y=winheight/2+30;
    xy.push_back(tmp);

    tmp.x=winwidth/2-30;
    tmp.y=winheight/2+30;
    xy.push_back(tmp);

}

void dragmouse(int x,int y){

    float ssx=1,ssy=1;
    float sssx=1,sssy=1;
    switch (mode)
    {
        case DRAWPOLYGON:
            break;
        case TRANSLATE:
            translation(x-tran_x,y-tran_y);
            transformedPoints();
            tran_x=x;
            tran_y=y;
            break;
        case ROTATE:
            if(x<=_xtmp&&y>=_ytmp)
                rotation(tran_x,tran_y,-8);
            else
                rotation(tran_x,tran_y,8);
            transformedPoints();
            _xtmp=x;
            _ytmp=y;
            break;
        case SCALE:
            if(x>_xtmp){
                ssx+=0.1f;
            }
            else if(x<_xtmp&&ssx>0){
                ssx-=0.1f;
            }
            if(y<_ytmp){
                ssy+=0.1f;
            }
            else if(y>_ytmp&&ssy>0){
                ssy-=0.1f;
            }

            scaling(ssx,ssy,tran_x,tran_y);
            transformedPoints();
            _xtmp=x;
            _ytmp=y;
            break;

        default:
            break;
    }
}

int arbx = 0, arby = 0;
void mymouse(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON &&state==GLUT_DOWN){
        switch (mode)
        {
        case TRANSLATE:
            tran_x=x;
            tran_y=y;
            break;
        case DRAWPOLYGON:
            tmp.x=x;
            tmp.y=y;
            xy.push_back(tmp);
            glutPostRedisplay();
            break;
        case ROTATE:
            tran_x=x;
            tran_y=y;
            arbx=x-winwidth/2;
            arby=winheight/2-y;
            break;
        case SCALE:
            tran_x=x;
            tran_y=y;
            break;
        case REFLECT:
            tran_x=x;
            tran_y=y;
            _xtmp=x;
            _ytmp=y;
            break;
        case SHEARING:
            tran_x=x;
            tran_y=y;
            _xtmp=x;
            _ytmp=y;
            break;
        default:
            break;
        }
    }

}

void keyboard(unsigned char key,int x,int y)
{
    switch(mode)
    {
        case DRAWPOLYGON:
            if(key == 115)
            {
                drawSquare();
                glutPostRedisplay();
            }
            if(key == 32)
            {
                xy.clear();
                glutPostRedisplay();
            }
            break;

        case ROTATE:
            if(key == 97)
            {
                rotation(tran_x,tran_y,-10);
                transformedPoints();
            }
            if(key == 100)
            {
                rotation(tran_x,tran_y,10);
                transformedPoints();
            }
            break;

        case REFLECT:
            if(key == 120)
            {
                reflection(120);
                transformedPoints();
            }
            if(key == 121)
            {
                reflection(121);
                transformedPoints();
            }
            if(key == 122)
            {
                reflection(122);
                transformedPoints();
            }

        case SHEARING:
            if(key == 97)
            {
                float ssx = 0.1, ssy = 0;
                Shearing(ssx,ssy,winwidth/2,winheight/2);
                transformedPoints();
            }
            if(key == 100)
            {
                float ssx = -0.1, ssy = 0;
                Shearing(ssx,ssy,winwidth/2,winheight/2);
                transformedPoints();
            }
            if(key == 119)
            {
                float ssx = 0, ssy = 0.1;
                Shearing(ssx,ssy,winwidth/2,winheight/2);
                transformedPoints();
            }
            if(key == 115)
            {
                float ssx = 0, ssy = -0.1;
                Shearing(ssx,ssy,winwidth/2,winheight/2);
                transformedPoints();
            }
            break;

    }
}

void displayMode(int mode)
{
    switch(mode)
    {
    case DRAWPOLYGON:
        writeOnScreen(300, 25, 0, "DRAWING MODE");
        break;
    case TRANSLATE:
        writeOnScreen(285, 25, 0, "TRANSLATION MODE");
        break;
    case ROTATE:
        writeOnScreen(300, 25, 0, "ROTATION MODE");
        break;
    case SCALE:
        writeOnScreen(300, 25, 0, "SCLAING MODE");
        break;
    case REFLECT:
        writeOnScreen(300, 25, 0, "REFLECTION MODE");
        break;
    case SHEARING:
        writeOnScreen(300, 25, 0, "SHEARING MODE");
        break;
    }
}

void conversion(int value, int x, int y)
{
    stringstream strm;
    strm << value;
    string xy = strm.str();
    char p[xy.length()];
    for (int i = 0; i < sizeof(p); i++)
        p[i] = xy[i];

    writeSmaller(x,y,0, p);
}

void displayInstructions(int mode)
{
    switch(mode)
    {
    case DRAWPOLYGON:
        writeSmaller(10, 570, 0, "INSTRUCTIONS:");
        writeSmaller(10, 590, 0, "s -> draw square");
        writeSmaller(10, 610, 0, "left click -> draw other shapes");
        writeSmaller(10, 630, 0, "Spacebar -> erase polygon");
        break;
    case TRANSLATE:
        writeSmaller(10, 590, 0, "INSTRUCTIONS:");
        writeSmaller(10, 610, 0, "drag mouse -> to translate");
        break;
    case ROTATE:
        writeSmaller(10, 490, 0, "Arbitrary Point:");
        writeSmaller(10, 510, 0, "x:");
        conversion(arbx, 20, 510);
        writeSmaller(10, 530, 0, "y:");
        conversion(arby, 20, 530);
        writeSmaller(10, 570, 0, "INSTRUCTIONS:");
        writeSmaller(10, 590, 0, "left click -> choose arbitrary point");
        writeSmaller(10, 610, 0, "a -> rotate anti-clockwise");
        writeSmaller(10, 630, 0, "d -> rotate clockwise");
        break;
    case SCALE:
        writeSmaller(10, 530, 0, "INSTRUCTIONS:");
        writeSmaller(10, 550, 0, "arbitrary point -> dragged from");
        writeSmaller(10, 570, 0, "drag mouse upward -> y-scale up");
        writeSmaller(10, 590, 0, "drag mouse downward -> y-scale down");
        writeSmaller(10, 610, 0, "drag mouse left -> x-scale down");
        writeSmaller(10, 630, 0, "drag mouse right -> x-scale up");
        break;
    case REFLECT:
        writeSmaller(10, 570, 0, "INSTRUCTIONS:");
        writeSmaller(10, 590, 0, "x -> about x-axis");
        writeSmaller(10, 610, 0, "y -> about y-axis");
        writeSmaller(10, 630, 0, "z -> about perpendicular to xy at origin");
        break;
    case SHEARING:
        writeSmaller(10, 530, 0, "INSTRUCTIONS:");
        writeSmaller(10, 550, 0, "(Shearing is done about origin)");
        writeSmaller(10, 570, 0, "w -> +ve y direction shear");
        writeSmaller(10, 590, 0, "s -> -ve y direction shear");
        writeSmaller(10, 610, 0, "a -> -ve x direction shear");
        writeSmaller(10, 630, 0, "d -> +ve x direction shear");
        break;
    }
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(20,winheight/2);
        glVertex2f(winwidth-20,winheight/2);
        glVertex2f(winwidth/2,40);
        glVertex2f(winwidth/2,winheight-40);
    glEnd();

    DrawPolygon();

    glColor3f(0,0,0);
   	displayMode(mode);
   	displayInstructions(mode);
    writeOnScreen(650, 610, 0, "Ishan Arora");
    glFlush();
}

void Menu(int id){
    if(id==0)
        mode=0;
    else if(id==1)
       mode=1;
    else if(id==2)
        mode=2;
    else if(id==3)
        mode=3;
    else if(id==4)
        mode=4;
    else if(id==5)
        mode=5;

    glutPostRedisplay();
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
    glutInitWindowPosition(350,100);
    glutInitWindowSize(winwidth,winheight);
    glutCreateWindow("2-D Transformations");
    init();
    int id=glutCreateMenu(Menu);
    glutAddMenuEntry("Drawing",0);
    glutAddMenuEntry("Translate",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Scale",3);
    glutAddMenuEntry("Reflect",4);
    glutAddMenuEntry("Shear",5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);
    glutMouseFunc(mymouse);
    glutMotionFunc(dragmouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
