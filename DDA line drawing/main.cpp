#include<GL/glut.h>
#include<iostream>
#include<string>
#include<sstream>
#include<math.h>
using namespace std;

void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,700,0,700);
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)h,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,700,0,700);
    glMatrixMode(GL_MODELVIEW);
}

void writeOnScreen(float x, float y, float z, char *str) {
  glRasterPos3f(x, y, z);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void DDA(float y1, float y2, float x1, float x2)
{
    float dy,dx,step,x,y,k,Xin,Yin;
    dx=x2-x1;
    dy=y2-y1;
    float slopeM = dy/dx;
    float step1 = 0;
    if(slopeM < 1)
        step1 = abs(dx);
    else if(slopeM > 1)
        step1 = abs (dy);
    else
        step1 = abs(slopeM);

    if(abs(dx)> abs(dy))
    {
        step = abs(dx);
    }
    else
        step = abs(dy);

    Xin = dx/step;
    Yin = dy/step;

    x= x1;
    y= y1;
    glPointSize(2);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();

    for (k=1 ;k<=step;k++)
    {
        x= x + Xin;
        y= y + Yin;

        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }
}

int totalPoints = -1;
float Cx[50] = {0};
float Cy[50] = {0};

void mouse(int button, int state, int x, int y)
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        y = glutGet(GLUT_WINDOW_HEIGHT) - y;
        totalPoints++;
        Cx[totalPoints] = x;
        Cy[totalPoints] = y;
        glutPostRedisplay();
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);

    float m = 0.0;
    glPointSize(7);
    if(totalPoints%2 != 0)
    {
        glBegin(GL_POINTS);
            glVertex2f(Cx[totalPoints], Cy[totalPoints]);
            glVertex2f(Cx[totalPoints-1], Cy[totalPoints-1]);
        glEnd();
        for(int i = 1; i <= totalPoints; i++)
        {
            if(i % 2 != 0)
                DDA(Cy[i-1], Cy[i], Cx[i-1], Cx[i]);
        }
        m = (Cy[totalPoints] - Cy[totalPoints-1])/(Cx[totalPoints] - Cx[totalPoints-1]);
    }
    else
    {
        glBegin(GL_POINTS);
            glVertex2f(Cx[totalPoints], Cy[totalPoints]);
        glEnd();
        for(int i = 1; i <= totalPoints; i++)
        {
            if(i % 2 != 0)
                DDA(Cy[i-1], Cy[i], Cx[i-1], Cx[i]);
        }
    }

    stringstream strm;
    strm << m;
    string slope = strm.str();
    char p[slope.length()];
    for (int i = 0; i < sizeof(p)-1; i++)
        p[i] = slope[i];

    writeOnScreen(580,100,0, p);
    writeOnScreen(500,100,0, "slope = ");
    writeOnScreen(500,30,0, "Ishan Arora");

    stringstream strs;
    int nooflines = totalPoints%2==0 ? (totalPoints/2): (totalPoints/2)+1;
    strs << nooflines;
    string temp_str = strs.str();
    char* char_type = (char*) temp_str.c_str();
    writeOnScreen(50,30,0, "total lines = ");
    writeOnScreen(200,30,0, char_type);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(250, 80);
    glutCreateWindow("Line Drawing DDA");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();
}
