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

void draw_pixel(int x, int y)
{
    glPointSize(2);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}
void bresenham(int y1, int y2, int x1, int x2)
{
    int dx, dy, i, p;
    int incx, incy, inc1, inc2;
    int x,y;
    dx = x2-x1;
    dy = y2-y1;
    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    incx = 1;
    if (x2 < x1) incx = -1;
    incy = 1;
    if (y2 < y1) incy = -1;
    x = x1; y = y1;
    if (dx > dy)
    {
        draw_pixel(x, y);
        p = 2 * dy-dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for (i=0; i<dx; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p += inc1;
            }
            else
                p += inc2;
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        draw_pixel(x, y);
        p = 2*dx-dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for (i=0; i<dy; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p += inc1;
            }
            else
                p += inc2;
            y += incy;
            draw_pixel(x, y);
        }
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
                bresenham(Cy[i-1], Cy[i], Cx[i-1], Cx[i]);
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
                bresenham(Cy[i-1], Cy[i], Cx[i-1], Cx[i]);
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
    glutCreateWindow("Bresenham's Line Drawing");

    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();
}
