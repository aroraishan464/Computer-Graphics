#include <GL/glut.h>
#include<math.h>

void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
}

void subInit()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 300);
}

void writeOnScreen(float x, float y, float z, char *str) {
  glRasterPos3f(x, y, z);

  for (char* c = str; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void circle(float x, float y, float radius){
	int i;
	int triangleAmount = 5;
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

struct Point {
	GLint x;
	GLint y;
};

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x, y+1, oldColor, newColor);
		floodFill(x-1, y, oldColor, newColor);
		floodFill(x, y-1, oldColor, newColor);
	}
	return;
}

int mPoints = 0;
int mainPolygonX[10] = {0};
int mainPolygonY[10] = {0};
void mainDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3);
    glColor3f(0,0,0);

    for(int i = 0; i< mPoints; i++)
    {
        circle(mainPolygonX[i], mainPolygonY[i], 4);
    }

    glBegin(GL_LINE_LOOP);
        for(int i = 0; i< mPoints; i++)
        {
            glVertex2f(mainPolygonX[i], mainPolygonY[i]);
        }
    glEnd();

    writeOnScreen(7,275,0, "USING  FLOOD  FILL");
    writeOnScreen(620,15,0, "Ishan Arora");
    glFlush();
}

void boundaryFill(int x, int y, float* fillColor, float* bc){
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
     color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2])){
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        boundaryFill(x+1,y,fillColor,bc);
        boundaryFill(x,y+1,fillColor,bc);
        boundaryFill(x-1,y,fillColor,bc);
        boundaryFill(x,y-1,fillColor,bc);
    }
}

int sPoints = 0;
int subPolygonX[10] = {0};
int subPolygonY[10] = {0};
void subDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3);
    glColor3f(1,1,1);

    for(int i = 0; i< sPoints; i++)
    {
        circle(subPolygonX[i], subPolygonY[i], 4);
    }

    glBegin(GL_LINE_LOOP);
        for(int i = 0; i< sPoints; i++)
        {
            glVertex2f(subPolygonX[i], subPolygonY[i]);
        }
    glEnd();
    writeOnScreen(7,275,0, "USING  BOUNDARY  FILL");
    glFlush();
}

void mainMouse(int button, int state, int x, int y)
{
    y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mainPolygonX[mPoints] = x;
        mainPolygonY[mPoints] = y;
        mPoints++;
        glutPostRedisplay();
    }
    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        float r = (rand()%100)/100.0;
        float g = (rand()%100)/100.0;
        float b = (rand()%100)/100.0;
        Color newColor = {r, g, b};
        Color oldColor = {1,1,1};

        floodFill(x, y, oldColor, newColor);
    }
}

void subMouse(int button, int state, int x, int y)
{
    y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        subPolygonX[sPoints] = x;
        subPolygonY[sPoints] = y;
        sPoints++;
        glutPostRedisplay();
    }
    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        int r = rand()%2;
        int g = rand()%2;
        float bCol[] = {1,1,1};
        float color[] = {r,g,1};
        boundaryFill(x,y,color,bCol);
    }
}

void mainKey(unsigned char key,int x,int y)
{
    if(key==32)
    {
        for(int i = 0 ; i<mPoints; i++)
        {
            mainPolygonX[i] = 0;
            mainPolygonY[i] = 0;
        }
        mPoints = 0;
        glutPostRedisplay();
    }
    if(key==27)
    {
        glutDestroyWindow(glutGetWindow());
    }
}
void subKey(unsigned char key,int x,int y)
{
    if(key==32)
    {
        for(int i = 0 ; i<sPoints; i++)
        {
            subPolygonX[i] = 0;
            subPolygonY[i] = 0;
        }
        sPoints = 0;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(800, 600);
    int mainWindow = glutCreateWindow("Filling Algorithms");
    init();
    glutDisplayFunc(mainDisplay);
    glutMouseFunc(mainMouse);
    glutKeyboardFunc(mainKey);

    glutCreateSubWindow(mainWindow, 0, 0, 800, 300);
    subInit();
    glutDisplayFunc(subDisplay);
    glutMouseFunc(subMouse);
    glutKeyboardFunc(subKey);
    glutMainLoop();
}
