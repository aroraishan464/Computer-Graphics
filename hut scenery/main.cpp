#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5, 32, 0, 26);
}

void hutTop();
void hutTopWindow();
void hutDown();
void tree();
void sun();
void cloud();

void rect(float shade, float a, float b, float c, float d)
{
    glColor3f(shade, shade, shade);
    glBegin(GL_POLYGON);
        glVertex2f(a, b);
        glVertex2f(c, b);
        glVertex2f(c, d);
        glVertex2f(a, d);
    glEnd();

}
void circle(float shade, float x, float y, float radius){
	int i;
	int triangleAmount = 20;
	float twicePi = 2.0f * 3.14;
	glColor3f(shade, shade, shade);
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

void hollowCircle(float x, float y, float radius){
	int i;
	int lineAmount = 100;
	float twicePi = 2.0f * 3.14;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void writeName(float x, float y, float z, char *string) {
  glRasterPos3f(x, y, z);

  for (char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    rect(0.8, -5, 0, 32, 10);
    hutTop();
    hutDown();
    hutTopWindow();
    tree();
    sun();
    cloud();

    //name
    glColor3f(0,0,0);
    writeName(23,3,0,"By");
    writeName(23,2,0,"Ishan Arora");
    glFlush();
}

void hutTop()
{
    glColor3f(0.9,0.9,0.9);
    glBegin(GL_POLYGON);
        glVertex2f(10, 17);
        glVertex2f(23, 17);
        glVertex2f(26, 11);
        glVertex2f(8, 11);
    glEnd();

    rect(0.8, 20, 17, 21, 17.5);
}

void hutTopWindow()
{
    glBegin(GL_TRIANGLES);
        glColor3f(0.8,0.8,0.8);
        glVertex2f(17.5, 16.5);
        glVertex2f(14, 13);
        glVertex2f(21, 13);
        glColor3f(0.2,0.2,0.2);
        glVertex2f(17.5, 16);
        glColor3f(0.85,0.85,0.85);
        glVertex2f(14.5, 13);
        glVertex2f(20.5, 13);
    glEnd();

    glColor3f(0.8,0.8,0.8);
    glBegin(GL_POLYGON);
        glVertex2f(15.5, 13.85);
        glVertex2f(17.5, 15.9);
        glVertex2f(19.5, 13.85);
        glVertex2f(19.2, 10.8);
        glVertex2f(15.8, 10.8);
    glEnd();

    circle(0.5, 17.5, 14.8, 0.5);
    rect(0.5, 16.5, 10.8, 18.5, 13.85);
    rect(0.8, 17.4, 10.9, 17.6, 13.77);
}

void hutDown()
{
    rect(0.7, 9, 6, 25, 11);
    rect(0.9, 15, 5.5, 20, 10.7);
    rect(0.7, 16, 5.5, 19, 10);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(16.7, 5.7);
        glVertex2f(18.4, 5.7);
        glVertex2f(18.4, 9);
        glVertex2f(16.7, 9);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3f(0.6,0.6,0.6);
        glVertex2f(17.1, 7.2);
        glVertex2f(18.1, 7.2);
        glColor3f(0.5,0.5,0.5);
        glVertex2f(18.1, 8.5);
        glVertex2f(17.1, 8.5);
    glEnd();
    glColor3f(0.3, 0.3, 0.3);
    hollowCircle(18.1, 6.8, 0.12);

    rect(0.9, 11, 8, 13, 10);
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_LINES);
        glVertex2f(12, 8);
        glVertex2f(12, 10);
        glVertex2f(11, 9);
        glVertex2f(13, 9);
    glEnd();
}

void bushes(float x, float y, float radius, float cradius, int lineAmount, float shade){
	int i;
	float arrx[lineAmount];
	float arry[lineAmount];
	float twicePi = 2.0f * 3.14;
    for(i = 0; i < lineAmount;i++) {
        arrx[i] = x + (radius * cos(i *  twicePi / lineAmount));
        arry[i] = y + (radius* sin(i * twicePi / lineAmount));
	}
    for(i = 0; i < lineAmount;i++) {
        circle(shade, arrx[i], arry[i], cradius);
    }
}

void tree()
{
    bushes(3.2, 12 , 3, 1.2, 9, 0.4);
    bushes(3.1, 12, 1.2, 1.25, 5, 0.5);
    bushes(3.1, 12, 0.4, 1, 1, 0.4);
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
        glVertex2f(2,5);
        glVertex2f(1, 4);
        glVertex2f(2.5,4.5);
        glVertex2f(3,4);
        glVertex2f(4, 4.5);
        glVertex2f(5,4);
        glVertex2f(4,5.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(2,5);
        glVertex2f(4, 5.5);
        glVertex2f(4,7);
        glVertex2f(4.2,8);
        glVertex2f(5,9);
        glVertex2f(3.7,9);
        glVertex2f(3.2,8);
        glVertex2f(2.5,7);
    glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(2.5,9);
        glVertex2f(1.8,9.5);
        glVertex2f(2.5,7);
        glVertex2f(3.2,8);
    glEnd();
}

void sun(){
    circle(0.7, 4,23, 2);
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_LINES);
        glVertex2f(4, 26.2);
        glVertex2f(4, 25.3);
        glVertex2f(4, 20);
        glVertex2f(4, 20.8);
        glVertex2f(1,23);
        glVertex2f(1.8,23);
        glVertex2f(6.2,23);
        glVertex2f(7,23);
        glVertex2f(1,20.5);
        glVertex2f(2.3,21.5);
        glVertex2f(5.7,24.2);
        glVertex2f(7,25.2);
        glVertex2f(1,25.2);
        glVertex2f(2.3,24.2);
        glVertex2f(5.7,21.5);
        glVertex2f(7,20.7);
    glEnd();
}

void cloud()
{
    bushes(26, 22 , 1, 1, 4, 0.9);
    bushes(28, 22 , 1, 1.2, 3, 0.9);
    bushes(15, 22 , 1, 1.2, 4, 0.9);
    bushes(17, 22 , 0.9, 1, 3, 0.9);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 650);
    glutCreateWindow("Hut Scenery");

    init();
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}
