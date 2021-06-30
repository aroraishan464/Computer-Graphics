#include <GL/glut.h>
#include <stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

void init(void)
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 900, 0, 500);
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,900,0,500);
    glMatrixMode(GL_MODELVIEW);
}

void circle(float x, float y, float radius){
	int i;
	int triangleAmount = 30;
	float twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
                x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

float scaleHeart = 0;
void heartEye()
{
    glPushMatrix();
    glTranslatef(365, 370, 0);
    glScalef(scaleHeart,scaleHeart,0);
    circle(-11, 2.45, 13);
    circle(11, 2.45, 13);
    glBegin(GL_TRIANGLES);
        glVertex2f(-25, 0);
        glVertex2f(25, 0);
        glVertex2f(0, -30);
    glEnd();
    glPopMatrix();
}

float degree = 0;
float p1 = -150;
float p2 = p1-36;
float p3 = -150;
float p4 = p3-36;
void crossEye()
{
    glPushMatrix();
    glTranslatef(470, 365,0);
    glRotatef(degree,0,0,1);
    glBegin(GL_POLYGON);
        glVertex2f(p2-2.5,-1*p2-2.5);
        glVertex2f(p2+2.5,-1*p2+2.5);
        glVertex2f(p1+2.5,-1*p1+2.5);
        glVertex2f(p1-2.5,-1*p1-2.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-1*p4-2.5, -1*p4+2.5);
        glVertex2f(-1*p4+2.5, -1*p4-2.5);
        glVertex2f(-1*p3+2.5, -1*p3-2.5);
        glVertex2f(-1*p3-2.5, -1*p3+2.5);
    glEnd();
    glPopMatrix();
}

float pa = -150;
float pb = -150;
void mouth()
{
    glPushMatrix();
    glTranslatef(417, 280, 0);
    glBegin(GL_POLYGON);
        glVertex2f(pa, -4);
        glVertex2f(pa, 4);
        glVertex2f(pb, 4);
        glVertex2f(pb, -4);
    glEnd();
    glPopMatrix();
}

float py = -4;
float pxa = -40;
float pxb = 40;
void coverRobo()
{
    glPushMatrix();
    glTranslatef(417, 280, 0);
    glBegin(GL_POLYGON);
        glVertex2f(pxa, -4);
        glVertex2f(pxa, py);
        glVertex2f(pxb, py);
        glVertex2f(pxb, -4);
    glEnd();
    glPopMatrix();
}

float covery = -4;
void nextFrame()
{
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(200, -4);
        glVertex2f(200, covery);
        glVertex2f(700, covery);
        glVertex2f(700, -4);
    glEnd();
}

float rface = 0;
void roboFace()
{
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(417, 280, 0);
    circle(5,0,rface);
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(-25, -40);
        glVertex2f(-25, -30);
        glVertex2f(40, -30);
        glVertex2f(40, -40);
    glEnd();
    glPopMatrix();
}

float rEyeSides = 0;
float eyeY = 0;
float rx = 7.5;
float rEye = 0;
void roboEye()
{
    glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(417, 300, 0);
    glColor3f(0,0,0);
    circle(-45,10,rEyeSides);
    circle(60,10,rEyeSides);
    glBegin(GL_POLYGON);
        glVertex2f(-45, 0);
        glVertex2f(-45, eyeY);
        glVertex2f(60, eyeY);
        glVertex2f(60, 0);
    glEnd();

    glColor3f(1,1,1);
    circle(rx, 10, rEye);
    glPopMatrix();
}

void writeOnScreen(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    heartEye();
    crossEye();
    mouth();
    coverRobo();
    nextFrame();
    roboFace();
    roboEye();
    glColor3f(0,0,0);
    writeOnScreen(400, 75, 0, "The End");
    writeOnScreen(700, 60, 0, "BY Ishan Arora");
    glutSwapBuffers();
}

void mainAnimFunc(int value);
void heartAnimFunc(int value);
void crossLeftMoveAnimFunc(int value);
void crossRightMoveAnimFunc(int value);
void mouthMoveAnimFunc(int value);
void crossRotateAnimFunc(int value);
void stretchRoboCoverFunc(int value);
void expandRoboCoverFunc(int value);
void nextFrameFunc(int value);
void makeRoboFaceFunc(int value);
void makeRoboEyeFunc(int value);
void openRoboEyeFunc(int value);
void moveRoboEyeFunc(int value);
void lastFrameFunc(int value);
void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    glutTimerFunc(0, mainAnimFunc, 0);
    glutPostRedisplay();
   }
}

int whichAnim = -1;
void mainAnimFunc(int value)
{
    whichAnim++;
    degree = 0;
    switch(whichAnim)
    {
        case 0:
            glutTimerFunc(0,heartAnimFunc,0);
            glutTimerFunc(2500, mainAnimFunc, 0);
            break;
        case 1:
            glutTimerFunc(0,crossLeftMoveAnimFunc,0);
            glutTimerFunc(500, mainAnimFunc, 0);
            break;
        case 2:
            glutTimerFunc(0,crossRightMoveAnimFunc,0);
            glutTimerFunc(500, mainAnimFunc, 0);
            break;
        case 3:
            glutTimerFunc(0, mouthMoveAnimFunc,0);
            glutTimerFunc(500, mainAnimFunc, 0);
            break;
        case 4:
            glutTimerFunc(0,heartAnimFunc,0);
            glutTimerFunc(0,crossRotateAnimFunc,0);
            glutTimerFunc(3300, mainAnimFunc, 0);
            break;
        case 5:
            glutPostRedisplay();
            glutTimerFunc(500, mainAnimFunc, 0);
            break;
        case 6:
            glutTimerFunc(0,stretchRoboCoverFunc,0);
            glutTimerFunc(200, mainAnimFunc, 0);
            break;
        case 7:
            glutTimerFunc(0,expandRoboCoverFunc,0);
            glutTimerFunc(200, mainAnimFunc, 0);
            break;
        case 8:
            glutTimerFunc(0,nextFrameFunc,0);
            glutTimerFunc(1000, mainAnimFunc, 0);
            break;
        case 9:
            glutTimerFunc(0,makeRoboFaceFunc,0);
            glutTimerFunc(1000, mainAnimFunc, 0);
            break;
        case 10:
            glutTimerFunc(0,makeRoboEyeFunc,0);
            glutTimerFunc(800, mainAnimFunc, 0);
            break;
        case 11:
            glutTimerFunc(0,openRoboEyeFunc,0);
            glutTimerFunc(1000, mainAnimFunc, 0);
            break;
        case 12:
            glutTimerFunc(0,moveRoboEyeFunc,0);
            glutTimerFunc(3000, mainAnimFunc, 0);
            break;
        case 13:
            glutTimerFunc(0,lastFrameFunc,0);
            glutTimerFunc(3000, mainAnimFunc, 0);
            break;
        case 14:
            glutDestroyWindow(glutGetWindow());
            break;
    }
}

int decrease=1;
int heartbeat = 0;
void heartAnimFunc(int value)
{
    if(decrease)
    {
        scaleHeart=scaleHeart-0.01f;
        if(scaleHeart<=0.9f)
        {
            decrease=0;
            heartbeat += 1;
            if(heartbeat%2==0 && heartbeat % 8 != 0)
                glutTimerFunc(400, heartAnimFunc, 0);
            else if(heartbeat % 8 != 0)
                glutTimerFunc(5, heartAnimFunc, 0);
        }
        else
            glutTimerFunc(5, heartAnimFunc, 0);
    }
    else
    {
        scaleHeart=scaleHeart+0.01f;
        if(scaleHeart>=1.1)
            decrease=1;
        glutTimerFunc(5, heartAnimFunc, 0);
    }
    glutPostRedisplay();
}

float inc1 = 0.1;
void crossLeftMoveAnimFunc(int value)
{
    inc1 += 0.16;
    if(p1<=15.5)
    {
        p1 += inc1;
        p2 += inc1;
        glutTimerFunc(5,crossLeftMoveAnimFunc,0);
    }
    glutPostRedisplay();
}

float inc2 = 0.1;
void crossRightMoveAnimFunc(int value)
{
    inc2 += 0.16;
    if(p3<=15.5)
    {
        p3 += inc2;
        p4 += inc2;
        glutTimerFunc(5,crossRightMoveAnimFunc,0);
    }
    glutPostRedisplay();
}

float inca = 0.1;
float incb = 0.1;
void mouthMoveAnimFunc(int value)
{
    inca += 0.1;
    incb += 0.2;
    if(pa <= -40)
        pa += inca;
    if(pb <= 40)
        pb += incb;
    if(pa <=-40 || pb <=40)
        glutTimerFunc(5,mouthMoveAnimFunc,0);
    glutPostRedisplay();
 }

void crossRotateAnimFunc(int value)
{
    if(degree <= 180)
    {
        degree += 0.25;
        if(degree == 45 || degree == 90 || degree == 135 )
            glutTimerFunc(580, crossRotateAnimFunc, 0);
        else
            glutTimerFunc(1.9, crossRotateAnimFunc, 0);
        glutPostRedisplay();
    }
}

float incx = 0.1;
void stretchRoboCoverFunc(int value)
{
    py = 4;
    incx += 0.1;
    if(pxa>=-100)
    {
        pxa -= incx;
        glutTimerFunc(5, stretchRoboCoverFunc,0);
    }
    if(pxb<=100)
        pxb += incx;
    glutPostRedisplay();
}

float incy = 0.1;
void expandRoboCoverFunc(int value)
{
    incy += 0.1;
    if(py<=550)
    {
        py += incy;
        glutTimerFunc(5, expandRoboCoverFunc,0);
    }
    glutPostRedisplay();
}

float fcy = 0.1;
void nextFrameFunc(int value)
{
    fcy += 0.1;
    if(covery<=550)
    {
        covery += fcy;
        glutTimerFunc(5, nextFrameFunc,0);
    }
    glutPostRedisplay();
}

float incr = 0.1;
int sizeDecrease = 0;
void makeRoboFaceFunc(int value)
{
    incr += 0.05;
    if(sizeDecrease==1)
    {
        rface -= incr;
        if(rface<=100)
        {
            sizeDecrease=2;
        }
        glutTimerFunc(5, makeRoboFaceFunc, 0);
    }
    if(sizeDecrease == 0)
    {
        rface += incr;
        if(rface>=130)
        {
            sizeDecrease=1;
        }
        glutTimerFunc(5, makeRoboFaceFunc, 0);
    }
    glutPostRedisplay();
}

float rinc = 0.5;
float rince = 0.1;
void makeRoboEyeFunc(int value)
{
    if(eyeY<=20)
    {
        eyeY += rinc;
        glutTimerFunc(5,makeRoboEyeFunc,0);
    }
    if(eyeY>20 && rEyeSides <=10)
    {
        rEyeSides += rince;
        glutTimerFunc(5,makeRoboEyeFunc,0);
    }
    glutPostRedisplay();
}

float rEyeInc = 0.05;
void openRoboEyeFunc(int value)
{
    if(rEye <= 6.8)
    {
        rEye += rEyeInc;
        glutTimerFunc(5, openRoboEyeFunc, 0);
    }
    glutPostRedisplay();
}

float rxincr1 = 0.01;
float rxincr2 = 0.01;
float rxincl = 0.01;
float moveLeft = 0 ;
void moveRoboEyeFunc(int value)
{
    if(moveLeft == 0)
    {
        rxincr1 += 0.005;
        if(rx <= 50)
        {
            rx += rxincr1;
            glutTimerFunc(5,moveRoboEyeFunc,0);
        }
        else
        {
            moveLeft = 1;
            glutTimerFunc(500,moveRoboEyeFunc,0);
        }
    }
    if(moveLeft == 1)
    {
        rxincr2 += 0.005;
        if(rx >= -20)
        {
            rx -= rxincr2;
            glutTimerFunc(10,moveRoboEyeFunc,0);
        }
        else
        {
            moveLeft = 2;
            glutTimerFunc(500,moveRoboEyeFunc,0);
        }
    }
    if(moveLeft == 2)
    {
        rxincl += 0.005;
        if(rx <= 5)
        {
            rx += rxincl;
            glutTimerFunc(12,moveRoboEyeFunc,0);
        }
        else
        {
            moveLeft = 3;
        }
    }
    glutPostRedisplay();
}

float rcoverInc = 0.1;
void lastFrameFunc(int value)
{
    rcoverInc += 0.1;
    if(rEye <= 910)
    {
        rEye += rcoverInc;
        glutTimerFunc(5,lastFrameFunc,0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300, 50);
    glutInitWindowSize(900, 500);
    glutCreateWindow("Short Robot Animation");

    init();
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
