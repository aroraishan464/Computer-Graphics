#include<GL/glut.h>
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<vector>
#include <fstream>

#define PI 3.14159265358
#define DRAWPOLYGON 0
#define TRANSLATE 1
#define ROTATE 2
#define SCALE 3
#define REFLECT 4
#define SHEARING 5
using namespace std;
int tran_x,tran_y;
int tran_z = 0;
int _xtmp,_ytmp;
int mode=DRAWPOLYGON;

typedef GLfloat Matrix4x4[4][4];
Matrix4x4 theMatrix;
float ptsFin[8][3];
float cx=0, cy=0, cz=0;
int arbx = 0, arby = 0, arbz = 0;
void DrawPolygon();
void dragmouse(int x,int y);
void mymouse(int button,int state,int x,int y);

void SetIdentity(Matrix4x4 m){
    int i, j;
    for (i=0; i<4; i++)
        for (j=0; j<4; j++)
            m[i][j] = (i == j);
}

void init(){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(-454.0, 454.0, -300.0, 300.0, -400.0, 400.0);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(3, 4, 5, 0, 0, 0, 0, 150, 0);
    SetIdentity(theMatrix);
}

void MultiplyMat(Matrix4x4 a , Matrix4x4 b)
{
    int i,j;
    Matrix4x4 tmp;
    for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
        tmp[i][j]=a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j]+a[i][3]*b[3][j];
    for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
        theMatrix[i][j] = tmp[i][j];
}

void writeOnScreen(float x, float y, float z, char *str) {
  glRasterPos2f(x, y);

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

void intToString(char * destStr, int val)
{
	sprintf(destStr,"%d",val);
}

void translation(int tx, int ty, int tz)
{
    Matrix4x4 m;
    SetIdentity(m);
    m[0][3] = tx;
    m[1][3] = ty;
    m[2][3] = tz;
    MultiplyMat(m, theMatrix);
}

void rotationX(int x, int y, int z, float theta){
    float tx = cx, ty=cy, tz=cz;
    theta=theta/180*PI;
    Matrix4x4 matRot;
    SetIdentity(matRot);

    matRot[1][1]=cos(theta);
    matRot[1][2]=sin(theta);
    matRot[1][3]=y*(1-cos(theta))-z*sin(theta);
    matRot[2][1]=-sin(theta);
    matRot[2][2]=cos(theta);
    matRot[2][3]=z*(1-cos(theta))+y*sin(theta);
    cy = ty*cos(theta)+tz*sin(theta)+ matRot[1][3];
    cz = -ty*sin(theta)+tz*cos(theta)+ matRot[2][3];

    MultiplyMat(matRot,theMatrix);
}

void rotationY(int x, int y, int z, float theta){
    float tx = cx, ty=cy, tz=cz;
    theta=theta/180*PI;
    Matrix4x4 matRot;
    SetIdentity(matRot);

    matRot[0][0]=cos(theta);
    matRot[0][2]=-sin(theta);
    matRot[0][3]=x*(1-cos(theta))+z*sin(theta);
    matRot[2][0]=sin(theta);
    matRot[2][2]=cos(theta);
    matRot[2][3]=z*(1-cos(theta))-x*sin(theta);
    cz = tx*sin(theta)+tz*cos(theta)+ matRot[2][3];
    cx = tx*cos(theta)-tz*sin(theta)+ matRot[0][3];

    MultiplyMat(matRot,theMatrix);
}

void rotationZ(int x, int y, int z, float theta){
    float tx = cx, ty=cy, tz=cz;
    theta=theta/180*PI;
    Matrix4x4 matRot;
    SetIdentity(matRot);

    matRot[0][0]=cos(theta);
    matRot[0][1]=sin(theta);
    matRot[0][3]=x*(1-cos(theta))-y*sin(theta);
    matRot[1][0]=-sin(theta);
    matRot[1][1]=cos(theta);
    matRot[1][3]=y*(1-cos(theta))+x*sin(theta);
    cx = tx*cos(theta)+ty*sin(theta)+ matRot[0][3];
    cy = -tx*sin(theta)+ty*cos(theta)+ matRot[1][3];

    MultiplyMat(matRot,theMatrix);
}

void scaling(GLfloat sx,GLfloat sy, GLfloat sz,int x,int y, int z)
{
    Matrix4x4 m;
    SetIdentity(m);
    m[0][0] = sx;
    m[0][3] = (1 - sx)*x;
    m[1][1] = sy;
    m[1][3] = (1 - sy)*y;
    m[2][2] = sz;
    m[2][3] = (1 - sy)*z;
    MultiplyMat(m , theMatrix);
}

void reflection(int x)
{
    if(x==120)
    {
        Matrix4x4 matrefl={{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};
        MultiplyMat(matrefl,theMatrix);
    }
    if(x==121)
    {
        Matrix4x4 matrefl={{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        MultiplyMat(matrefl,theMatrix);
    }
    if(x==122)
    {
        Matrix4x4 matrefl={{1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,0,1}};
        MultiplyMat(matrefl,theMatrix);
    }
}

void Shearing(GLfloat sx,GLfloat sy, GLfloat sz)
{
    Matrix4x4 matShear ={{1,sy,sz,0},{sx,1,sz,0},{sx,sy,1,0},{0,0,0,1}};
    MultiplyMat(matShear,theMatrix);
}

void transformedPoints(){
    int i,k;
    float ptsIni[8][3];
    for(k=0 ; k<8 ; k++)
        for (i=0 ; i<3 ; i++)
            ptsIni[k][i]=ptsFin[k][i];
    for(k=0 ; k<8 ; k++)
        for (i=0 ; i<3 ; i++)
            ptsFin[k][i] = theMatrix[i][0]*ptsIni[k][0] + theMatrix[i][1]*ptsIni[k][1]
                + theMatrix[i][2]*ptsIni[k][2] + theMatrix[i][3];
    if(mode != ROTATE){
        for(i=0; i<3; i++)
        {
            if(i==0)
                cx = theMatrix[i][0]*cx + theMatrix[i][1]*cy + theMatrix[i][2]*cz + theMatrix[i][3];
            if(i==1)
                cy = theMatrix[i][0]*cx + theMatrix[i][1]*cy + theMatrix[i][2]*cz + theMatrix[i][3];
            if(i==2)
                cz = theMatrix[i][0]*cx + theMatrix[i][1]*cy + theMatrix[i][2]*cz + theMatrix[i][3];
        }
    }
    glutPostRedisplay();
    SetIdentity(theMatrix);
}

void DrawPolygon(float a[8][3])
{
    int i;
    glColor3f (0.3, 0.4, 0.1);
    glBegin(GL_POLYGON);
        glVertex3f(a[0][0],a[0][1],a[0][2]);
        glVertex3f(a[1][0],a[1][1],a[1][2]);
        glVertex3f(a[2][0],a[2][1],a[2][2]);
        glVertex3f(a[3][0],a[3][1],a[3][2]);
    glEnd();
    i=0;
    glColor3f (0.1, 0.6, 0.5);
    glBegin(GL_POLYGON);
        glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
        glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
        glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
        glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
    glEnd();
    glColor3f (0.1, 0.9, 0.7);
    glBegin(GL_POLYGON);
        glVertex3f(a[0][0],a[0][1],a[0][2]);
        glVertex3f(a[3][0],a[3][1],a[3][2]);
        glVertex3f(a[7][0],a[7][1],a[7][2]);
        glVertex3f(a[4][0],a[4][1],a[4][2]);
    glEnd();
    i=1;
    glColor3f (0.1, 0.4, 0.3);
    glBegin(GL_POLYGON);
        glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
        glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
        glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
        glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
    glEnd();
    i=2;
    glColor3f (0.5, 0.1, 0.2);
    glBegin(GL_POLYGON);
        glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
        glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
        glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
        glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
    glEnd();
    i=4;
    glColor3f (0.1, 0.3, 0.4);
    glBegin(GL_POLYGON);
        glVertex3f(a[0+i][0],a[0+i][1],a[0+i][2]);
        glVertex3f(a[1+i][0],a[1+i][1],a[1+i][2]);
        glVertex3f(a[2+i][0],a[2+i][1],a[2+i][2]);
        glVertex3f(a[3+i][0],a[3+i][1],a[3+i][2]);
    glEnd();
}

void drawCuboid()
{
    float random[8][4]={{-30,-30,60},{30,-30,60},{30,30,60},{-30,30,60},
                        {-30,-30,-60},{30,-30,-60},{30,30,-60},{-30,30,-60}};
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            ptsFin[i][j]=random[i][j];
}

void drawCube()
{
    float random[8][4]={{-30,-30,30},{30,-30,30},{30,30,30},{-30,30,30},
                        {-30,-30,-30},{30,-30,-30},{30,30,-30},{-30,30,-30}};
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            ptsFin[i][j]=random[i][j];
}
void drawOctahedron()
{
    float random[8][4]={{-30,0,30},{0,-30,0},{30,0,30},{0,30,0},
                        {-30,0,-30},{0,-30,0},{30,0,-30},{0,30,0}};
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            ptsFin[i][j]=random[i][j];
}

void erasePolygon()
{
    for(int i = 0; i<8; i++)
        for(int j = 0; j<3; j++)
            ptsFin[i][j] = 0;
}

void dragmouse(int x,int y){

    float ssx=1,ssy=1;
    float sssx=1,sssy=1;
    switch (mode)
    {
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

            scaling(ssx,ssy,1,arbx, arby, arbz);
            transformedPoints();
            _xtmp=x;
            _ytmp=y;
            break;

        default:
            break;
    }
}

int sub=10;
void moveArbitraryPoint(unsigned char key)
{
    if(key == 'a')
        arbx-=sub;

    if(key == 'd')
        arbx+=sub;

    if(key == 'w')
        arby+=sub;

    if(key == 's')
        arby-=sub;

    if(key == 'i')
        arbz+=sub;

    if(key == 'k')
        arbz-=sub;
}

void keyboard(unsigned char key,int x,int y)
{
    int ssz = 1;
    float tx,ty,tz,theta;
    switch(mode)
    {
        case DRAWPOLYGON:
            cx = 0, cy = 0, cz = 0;
            if(key == 'c')
                drawCuboid();
            if(key == 's')
                drawCube();
            if(key == 'o')
                drawOctahedron();
            if(key == 32){
                erasePolygon();
            }
            glutPostRedisplay();
            break;

        case TRANSLATE:
            if(key == 'a'){
                translation(-sub,0,0);
                transformedPoints();
            }
            if(key == 'd'){
                translation(sub,0,0);
                transformedPoints();
            }

            if(key == 'w'){
                translation(0,sub,0);
                transformedPoints();
            }
            if(key == 's'){
                translation(0,-sub,0);
                transformedPoints();
            }

            if(key == 'i'){
                translation(0,0,sub);
                transformedPoints();
            }
            if(key == 'k'){
                translation(0,0,-sub);
                transformedPoints();
            }

            glutPostRedisplay();
            break;

        case SCALE:
            moveArbitraryPoint(key);
            if(key == 'j')
            {
                ssz-=0.1f;
                scaling(1,1,0.8,arbx, arby, arbz);
                transformedPoints();
            }
            if(key == 'l')
            {
                ssz+=0.1f;
                scaling(1,1,1.2,arbx, arby, arbz);
                transformedPoints();
            }

            glutPostRedisplay();
            break;

        case ROTATE:
            moveArbitraryPoint(key);
            if(key == 'y')
                rotationY(arbx, arby, arbz, 20);
            if(key == 'x')
                rotationX(arbx, arby, arbz, 20);
            if(key == 'z')
                rotationZ(arbx, arby, arbz, 20);
            transformedPoints();
            break;

        case REFLECT:
            if(key == 'x')
                reflection(120);
            if(key == 'y')
                reflection(121);
            if(key == 'z')
                reflection(122);

            transformedPoints();
            break;

        case SHEARING:
            if(key == 'a')
            {
                float ssx = 0.1, ssy = 0, ssz = 0;
                Shearing(ssx,ssy,ssz);
            }
            if(key == 'd')
            {
                float ssx = -0.1, ssy = 0, ssz=0;
                Shearing(ssx,ssy,ssz);
            }
            if(key == 'w')
            {
                float ssx = 0, ssy = -0.1, ssz=0;
                Shearing(ssx,ssy,ssz);
            }
            if(key == 's')
            {
                float ssx = 0, ssy = 0.1, ssz=0;
                Shearing(ssx,ssy,ssz);
            }
            if(key == 'k')
            {
                float ssx = 0, ssy = 0, ssz=0.1;
                Shearing(ssx,ssy,ssz);
            }
            if(key == 'i')
            {
                float ssx = 0, ssy = 0, ssz=-0.1;
                Shearing(ssx,ssy,ssz);
            }
            transformedPoints();
            break;

    }
}

void displayMode(int mode)
{
    switch(mode)
    {
    case DRAWPOLYGON:
        writeOnScreen(-110, 290, 0, "DRAWING MODE");
        break;
    case TRANSLATE:
        writeOnScreen(-130, 283, 0, "TRANSLATION MODE");
        break;
    case ROTATE:
        writeOnScreen(-110, 293, 0, "ROTATION MODE");
        break;
    case SCALE:
        writeOnScreen(-110, 293, 0, "SCLAING MODE");
        break;
    case REFLECT:
        writeOnScreen(-130, 283, 0, "REFLECTION MODE");
        break;
    case SHEARING:
        writeOnScreen(-110, 293, 0, "SHEARING MODE");
        break;
    }
}

void displayCenter()
{
    char cxBuffer [33];
    char cyBuffer [33];
    char czBuffer [33];
    intToString(cxBuffer, cx);
    intToString(cyBuffer, cy);
    intToString(czBuffer, cz);

    writeSmaller(-510,130,0, "Center:");
    writeSmaller(-510,110,0, "x: ");
    writeSmaller(-495,115,0, cxBuffer);
    writeSmaller(-510,90,0, "y: ");
    writeSmaller(-495,95,0, cyBuffer);
    writeSmaller(-510,70,0, "z: ");
    writeSmaller(-495,75,0, czBuffer);
}

void displayInstructions(int mode)
{
    char arbxBuffer [33];
    char arbyBuffer [33];
    char arbzBuffer [33];
    intToString(arbxBuffer, arbx);
    intToString(arbyBuffer, arby);
    intToString(arbzBuffer, arbz);

    switch(mode)
    {
    case DRAWPOLYGON:
        writeSmaller(-270, -110, 400, "INSTRUCTIONS:");
        writeSmaller(-270, -130, 400, "s -> draw cube");
        writeSmaller(-270, -150, 400, "c -> draw cuboid");
        writeSmaller(-270, -170, 400, "o -> draw octahedron");
        writeSmaller(-270, -190, 400, "Spacebar -> erase polygon");
        break;

    case TRANSLATE:
        writeSmaller(-270, -70, 400, "INSTRUCTIONS:");
        writeSmaller(-270, -90, 400, "a -> -ve x");
        writeSmaller(-270, -110, 400, "d -> +ve x");
        writeSmaller(-270, -130, 400, "w -> +ve y");
        writeSmaller(-270, -150, 400, "s -> -ve y");
        writeSmaller(-270, -170, 400, "i -> +ve z");
        writeSmaller(-270, -190, 400, "k -> -ve z");
        break;

    case ROTATE:
        glColor3f(1,1,0);
        glBegin(GL_POINTS);
            glVertex3f(arbx, arby, arbz);
        glEnd();

        glColor3f(0.48,0.40,0.93);
        glBegin(GL_LINES);
            glVertex3f(454, arby, arbz);
            glVertex3f(-454, arby, arbz);
            glVertex3f(arbx, 300, arbz);
            glVertex3f(arbx, -300, arbz);
            glVertex3f(arbx, arby, 400);
            glVertex3f(arbx, arby, -400);
        glEnd();

        glColor3f(1,1,1);
        writeSmaller(-270, 150, 400, "arbitrary pt.:");
        writeSmaller(-270,130,400, "x: ");
        writeSmaller(-257,133,400, arbxBuffer);
        writeSmaller(-270,110,400, "y: ");
        writeSmaller(-257,113,400, arbyBuffer);
        writeSmaller(-270,90,400, "z: ");
        writeSmaller(-257,92,400, arbzBuffer);

        glColor3f(1,1,1);
        writeSmaller(-270, 50, 400, "INSTRUCTIONS:");
        writeSmaller(-270, 30, 400, "( for arbitrary point )");
        writeSmaller(-270, 10, 400, "a -> -ve x");
        writeSmaller(-270, -10, 400, "d -> +ve x");
        writeSmaller(-270, -30, 400, "w -> +ve y");
        writeSmaller(-270, -50, 400, "s -> -ve y");
        writeSmaller(-270, -70, 400, "i -> +ve z");
        writeSmaller(-270, -90, 400, "k -> -ve z");

        writeSmaller(-270, -130, 400, "( rotation clockwise )");
        writeSmaller(-270, -150, 400, "x -> about x-axis");
        writeSmaller(-270, -170, 400, "y -> about y-axis");
        writeSmaller(-270, -190, 400, "z -> about z-axis");
        break;

    case SCALE:
        glColor3f(1,1,0);
        glBegin(GL_POINTS);
            glVertex3f(arbx, arby, arbz);
        glEnd();

        glColor3f(1,1,1);
        writeSmaller(-270, 150, 400, "arbitrary pt.:");
        writeSmaller(-270,130,400, "x: ");
        writeSmaller(-257,133,400, arbxBuffer);
        writeSmaller(-270,110,400, "y: ");
        writeSmaller(-257,113,400, arbyBuffer);
        writeSmaller(-270,90,400, "z: ");
        writeSmaller(-257,92,400, arbzBuffer);

        writeSmaller(-270, 50, 400, "INSTRUCTIONS:");
        writeSmaller(-270, 30, 400, "( for arbitrary point )");
        writeSmaller(-270, 10, 400, "a -> -ve x");
        writeSmaller(-270, -10, 400, "d -> +ve x");
        writeSmaller(-270, -30, 400, "w -> +ve y");
        writeSmaller(-270, -50, 400, "s -> -ve y");
        writeSmaller(-270, -70, 400, "i -> +ve z");
        writeSmaller(-270, -90, 400, "k -> -ve z");

        writeSmaller(-270, -120, 400, "( for scaling )");
        writeSmaller(-270, -140, 400, "drag horizontal -> x scaling");
        writeSmaller(-270, -160, 400, "drag vertical -> y scaling");
        writeSmaller(-270, -180, 400, "j -> z scale down");
        writeSmaller(-270, -200, 400, "l -> z scale up");
        break;

    case REFLECT:
        writeSmaller(-270, -130, 400, "INSTRUCTIONS:");
        writeSmaller(-270, -150, 400, "x -> relative to yz-plane");
        writeSmaller(-270, -170, 400, "y -> relative to xz-plane");
        writeSmaller(-270, -190, 400, "z -> relative to xy-plane");
        break;

    case SHEARING:
        writeSmaller(-270, -50, 400, "INSTRUCTIONS:");
        writeSmaller(-270, -70, 400, "( about origin )");
        writeSmaller(-270, -90, 400, "a -> -ve x");
        writeSmaller(-270, -110, 400, "d -> +ve x");
        writeSmaller(-270, -130, 400, "w -> +ve y");
        writeSmaller(-270, -150, 400, "s -> -ve y");
        writeSmaller(-270, -170, 400, "i -> +ve z");
        writeSmaller(-270, -190, 400, "k -> -ve z");
        break;
    }
}

void Display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(2);
    glColor3f (0.7, 0.4, 0.5);
    glBegin(GL_LINES);
        glVertex2f(-454 ,0);
        glVertex2f( 454 ,0);
        glVertex2f(0 ,-300);
        glVertex2f(0 , 300);
        glVertex3f(0,0,-400);
        glVertex3f(0,0,400);
    glEnd();
    writeSmaller(-454,0,0,"-x");
    writeSmaller(454,0,0,"+x");
    writeSmaller(0,-300,0,"-y");
    writeSmaller(0,300,0,"+y");
    writeSmaller(0,0,-400,"-z");
    writeSmaller(0,0,400,"+z");
    glPointSize(10);

    DrawPolygon(ptsFin);

    glColor3f(1,1,1);
    displayCenter();
    displayMode(mode);
   	displayInstructions(mode);
   	writeOnScreen(370, -190, 0, "Ishan Arora");
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
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (910, 600);
    glutInitWindowPosition (300, 100);
    glutCreateWindow("3-D Transformations");
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
    glutMotionFunc(dragmouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
