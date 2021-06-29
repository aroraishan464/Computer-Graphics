#include <GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

void init()
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600);
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
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
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
	glPointSize(1);
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

class Point {
public:
    float x, y;
    void setxy(float x2, float y2)
    {
        x = x2; y = y2;
    }

    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }
};

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}

int clicks = 4;
void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
      glVertex2f(p1.x, p1.y);
      glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}

Point drawBezierGeneralized(Point PT[], double t) {
    Point P;
    P.x = 0; P.y = 0;
    for (int i = 0; i<clicks; i++)
    {
        P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
        P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
    }
    return P;
}
void drawCurve(Point x[])
{
    glColor3f(0.8,0.8,0.8);
    Point p1 = x[0];
    for(double t = 0.0;t <= 1.0; t += 0.02)
    {
        Point p2 = drawBezierGeneralized(x,t);
        drawLine(p1, p2);

        p1 = p2;
    }
    glColor3f(0.0,0.0,0.0);
}
void shapeCoordinates()
{
    glColor3f(0.8,0.8,0.8);
    hollowCircle(280, 515, 23);

    Point eyel[8]={{365,450},{360,450},{345,430},{300,440},{320,425},{320,417},{345,410},{365,415}};
    clicks=8;
    drawCurve(eyel);

    Point eyer[4]={{362,415},{370,425},{370,450},{365,450}};
    clicks=4;
    drawCurve(eyer);

    Point frd[4]={{303,520},{370,530},{395,480},{385,440}};
    clicks=4;
    drawCurve(frd);

    Point fre[4]={{386,442},{377,453},{378,425},{380,405}};
    clicks=4;
    drawCurve(fre);


    Point nd1[3]={{380,407},{367,407},{382,393}};
    clicks=3;
    drawCurve(nd1);

    Point nd2[3]={{383,395},{373,382},{358,379}};
    clicks=3;
    drawCurve(nd2);

    Point fru1[4]={{300,527},{325,533},{350,525},{362,513}};
    clicks=4;
    drawCurve(fru1);

    Point earr[5]={{360,515},{373,513},{377,520},{397,507},{387,480}};
    clicks=5;
    drawCurve(earr);

    Point fru2[6]={{389,482},{384,470},{397,467},{396,440},{370,413},{389,400}};
    clicks=6;
    drawCurve(fru2);

    Point nu1[5]={{387,402},{392,398},{391,392},{381,379},{365,374}};
    clicks=5;
    drawCurve(nu1);

    Point hb1[3]={{263,498},{245,475},{253,430}};
    clicks=3;
    drawCurve(hb1);

    Point hb2[3]={{268,495},{250,475},{263,434}};
    clicks=3;
    drawCurve(hb2);

    Point bu[5]={{232,395},{275,520},{300,340},{410,400},{370,340}};
    clicks=5;
    drawCurve(bu);

    Point bd[5]={{232,395},{250,415},{340,385},{320,350},{345,345}};
    clicks=5;
    drawCurve(bd);

    Point leg[6]={{330,290},{312,342},{350,385},{425,345},{395,297},{375,289}};
    clicks=6;
    drawCurve(leg);

    Point au[4]={{228,385},{185,300},{235,280},{337,292}};
    clicks=4;
    drawCurve(au);

    Point ad[3]={{228,385},{190,310},{220,295}};
    clicks=3;
    drawCurve(ad);

    Point s1[3]={{220,295},{200,295},{170,290}};
    clicks=3;
    drawCurve(s1);

    Point s2[3]={{375,289},{395,289},{425,284}};
    clicks=3;
    drawCurve(s2);

    Point s3[4]={{170,290},{200,282},{295,278},{430,284}};
    clicks=4;
    drawCurve(s3);
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

void writtenCoordinates()
{
    glLineWidth(1);

    glColor3f(0.8,0.8,0.8);

    //p
    triangle(85,150,115,150,100,250);
    triangle(100,250,150,225,137,218);
    triangle(110,180,150,225,109,200);

    //a
    triangle(200,250,175,150,155,150);
    triangle(200,250,195,225,235,150);

    //n
    triangle(250,150,260,250,270,150);
    triangle(260,250,315,150,265,210);
    triangle(315,150,300,250,325,250);

    //d
    triangle(350,250,335,150,365,150);
    triangle(350,250,410,200,390,200);
    triangle(365,150,410,200,390,200);

    //a
    triangle(455,250,430,150,410,150);
    triangle(455,250,450,225,490,150);
}

void grid()
{
    int line = 50;
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
    for(int i=0; i<12; i++)
    {
        glVertex2f(0,line);
        glVertex2f(600,line);
        glVertex2f(line,0);
        glVertex2f(line,600);
        line += 50;
    }
    glEnd();
}

Color newColor;
Color oldColor = {1,1,1};
void fillRandomColor()
{
    float r = (rand()%100)/100.0;
    float g = (rand()%100)/100.0;
    float b = (rand()%100)/100.0;
    newColor = {r, g, b};
}

int renderShape = 0;
int fillShape = 0;
void mainDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);

    //grid();
    if(renderShape)
    {
        shapeCoordinates();
        writtenCoordinates();
    }

    if(fillShape)
    {

        oldColor = {1,1,1};
        newColor = {0,0,0};
        floodFill(355, 440, oldColor, newColor);
        floodFill(275, 525, oldColor, newColor);
        floodFill(305, 525, oldColor, newColor);
        floodFill(261, 490, oldColor, newColor);
        floodFill(275, 430, oldColor, newColor);
        floodFill(350, 340, oldColor, newColor);

        fillRandomColor();
        floodFill(100, 230, oldColor, newColor);
        floodFill(145, 225, oldColor, newColor);
        floodFill(113, 200, oldColor, newColor);

        fillRandomColor();
        floodFill(162, 160, oldColor, newColor);
        floodFill(200, 225, oldColor, newColor);

        fillRandomColor();
        floodFill(260, 200, oldColor, newColor);
        floodFill(275, 210, oldColor, newColor);
        floodFill(310, 225, oldColor, newColor);

        fillRandomColor();
        floodFill(350, 200, oldColor, newColor);
        floodFill(400, 205, oldColor, newColor);
        floodFill(400, 195, oldColor, newColor);

        fillRandomColor();
        floodFill(420, 160, oldColor, newColor);
        floodFill(460, 225, oldColor, newColor);

    }
    glColor3f(0,0,0);
    writeOnScreen(440,15,0,"By Ishan Arora");
    writeSmaller(10,20,0,"(Panda made using Bezier curves)");
    glFlush();
}

void mainMouse(int button, int state, int x, int y)
{
    y = glutGet( GLUT_WINDOW_HEIGHT ) - y;
    if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        renderShape = 1;
    if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        fillShape = 1;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(400,50);
    glutInitWindowSize(600, 600);
    int mainWindow = glutCreateWindow("Bezier Curves");
    init();
    glutDisplayFunc(mainDisplay);
    glutMouseFunc(mainMouse);
    glutMainLoop();
}
