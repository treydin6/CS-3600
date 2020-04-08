//// Bezier Surfaces Demo.
// Treydin Winward
// Spring 2020

#define GL_SILENCE_DEPRECATION
#include "GLUT/glut.h"
#include <math.h>
#include "graphics.h"
#include <iostream>
#include <vector>
#include <time.h>


//double curquat[4];

std::vector<Bezier> Curves;
std::pair <int, int> Points;
int selectedCurve = -1;

Point2::Point2()
    : x(0), y(0) {
}

Point2::Point2(double x, double y)
    : x(x), y(y) {
}

Point2 Point2::operator*(const double &rhs) {
    return Point2(x * rhs, y * rhs);
}

Point2 Point2::operator+(const Point2 &rhs) {
    return Point2(x + rhs.getX(), y + rhs.getY());
}

void DrawCircle(int x1, int y1, int radius, double r, double g, double b) {
    glBegin(GL_POLYGON);
    glColor3d(r, g, b);
    for (int i = 0; i<32; i++)
    {
        double theta = (double)i / 32.0 * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

Point2 Bezier::Evaluate(float t) {
    Point2 evalCurve;
    float n = 1 - t;

    evalCurve.x = points[0].getX() * n*n*n + 3 * points[1].getX()*n*n*t + 3 * points[2].getX()*n*t*t + points[3].getX()*t*t*t;
    evalCurve.y = points[0].getY() * n*n*n + 3 * points[1].getY()*n*n*t + 3 * points[2].getY()*n*t*t + points[3].getY()*t*t*t;

    return evalCurve;
}

void Bezier::DrawCurve() {
    int sections = 20;
    double inc = 1.0 / sections;
    for (double t = 0; t < 1; t += inc) {
        Point2 p1 = Evaluate(t);
        Point2 p2 = Evaluate(t + inc);
        
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3d(color[0], color[1], color[2]);
        glVertex2f(p1.getX(), p1.getY());
        glVertex2f(p2.getX(), p2.getY());
        
        glEnd();
    }
}

void Bezier::DrawControlPoints() {
    for (int i = 0; i < 4; i++) {
        DrawCircle(points[i].getX(), points[i].getY(), radius, color[0], color[1], color[2]);
    }
}

// returns <n> if x,y is within <radius> of control point <n>.
// returns -1 if x,y is not close to any of the 4 control points.
int Bezier::IsPicked(float x, float y) {
    for (int i = 0; i < 4; i++) {
        double x2 = points[i].getX();
        double y2 = points[i].getY();
        double dist = (x2 - x)*(x2 - x) + (y2 - y)*(y2 - y);
        dist = sqrt(dist);
        if (dist < radius)
            return i;
    }
    return -1;
}

void DrawSphere(float x, float y, float z, float radius)
{
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
    
    
}


// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLfloat redMaterial[] = {0.7f, 0.1f, 0.2f, 1.0f};
GLfloat greenMaterial[] = {0.1f, 0.7f, 0.4f, 1.0f};
GLfloat brightGreenMaterial[] = {0.1f, 0.9f, 0.1f, 1.0f};
GLfloat blueMaterial[] = {0.1f, 0.2f, 0.7f, 1.0f};
GLfloat whiteMaterial[] = {1.0f, 1.0f, 1.0f, 1.0f};

int screen_x = 900;
int screen_y = 700;


void DrawRectangle(int x1, int y1, int x2, int y2)
{
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

// Outputs a string of text at the specified location.
void text_output(int x, int y, char *string)
{
    void *font = GLUT_BITMAP_9_BY_15;
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
    
    glDisable(GL_BLEND);
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (unsigned  int i = 0; i < Curves.size(); i++) {
        Curves[i].DrawCurve();
        Curves[i].DrawControlPoints();
    }
   
    glutSwapBuffers();
    glutPostRedisplay();
}



void keyboard(unsigned char c, int x, int y)
{
    switch (c) {
        case 27: // escape character means to quit the program
            exit(0);
            break;
        case 'b':
            // do something when 'b' character is hit.
            break;
        default:
            return;
    }
    glutPostRedisplay();
}


void SetPerspectiveView(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (GLdouble) w/(GLdouble) h;
    gluPerspective(
    /* field of view in degree */ 38.0,
    /* aspect ratio */ aspectRatio,
    /* Z near */ .9, /* Z far */ 100.0);
    gluLookAt(0,0,5,  0,0,0,  0,1,0);
    glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
    screen_x = w;
    screen_y = h;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}


// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
    y=screen_y-y-1; /* orient screen so 0,0 is bottom left, not top left */
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        for (unsigned int i = 0; i < Curves.size(); i++) {
            int j = Curves[i].IsPicked(x, y);
            if (j != -1) {
                Points.first = i;
                Points.second = j;
                
                selectedCurve = i;
            }
        }
    }
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        Points.first = -1;
        Points.second = -1;
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON)
    {
    }
    
    glutPostRedisplay();
}

void mousemotion(int x, int y){
    
    if (Points.first != -1) {
        
        //invert mouse coords
        int Y = screen_y - y;
        
        Curves[Points.first].points[Points.second].x = x;
        Curves[Points.first].points[Points.second].y = Y;
    }
    
}

int getX(){
    int x = rand() % screen_x;
    while(x < 10 || x > screen_x - 10){
        x = rand() % screen_x;
    }
    //std::cout << "X = " << x << std::endl;
    return x;
}

int getY() {
    int y = rand() % screen_y;
    while(y < 10 || y > screen_y - 10){
        y = rand() % screen_y;
    }
    //std::cout << "Y = " << y << std::endl << std::endl << std::endl;
    return y;
}

double getColor(){
    return ((rand() % 255) + 1) / 255.;
}

void addBezier() {
    srand(time(NULL));
    if(Curves.size() > 4){
        return;
    }
    Bezier curve;
    
    
    Point2 first(getX(), getY());
    Point2 second(getX(), getY());
    Point2 third(getX(), getY());
    Point2 fourth(getX(), getY());
    

    curve.points[0] = first;
    curve.points[1] = second;
    curve.points[2] = third;
    curve.points[3] = fourth;
    curve.color[0] = getColor();
    curve.color[1] = getColor();
    curve.color[2] = getColor();
    Curves.push_back(curve);
}

// Your initialization code goes here.

void menu(int id) {
    if (id == 1) {
        exit(0);
    }
    else if (id == 2){
        addBezier();
    }
    glutPostRedisplay();
}

void colors(int id) {
    if (selectedCurve != -1) {
        if (id == 1) {
            Curves[selectedCurve].color[0] = 1;
            Curves[selectedCurve].color[1] = 0;
            Curves[selectedCurve].color[2] = 0;
        } else if (id == 2) {
            Curves[selectedCurve].color[0] = 0;
            Curves[selectedCurve].color[1] = 1;
            Curves[selectedCurve].color[2] = 0;
        } else if (id == 3) {
            Curves[selectedCurve].color[0] = 0;
            Curves[selectedCurve].color[1] = 0;
            Curves[selectedCurve].color[2] = 1;
        } else if (id == 4) {
            Curves[selectedCurve].color[0] = 1;
            Curves[selectedCurve].color[1] = 1;
            Curves[selectedCurve].color[2] = 0;
        } else if (id == 5) {
            Curves[selectedCurve].color[0] = 1;
            Curves[selectedCurve].color[1] = 1;
            Curves[selectedCurve].color[2] = 1;
        }
    }
    glutPostRedisplay();
}

void InitializeMyStuff(){
    addBezier(); // adds 1 curve to the screen when app loads.
    
    int colorMenu = glutCreateMenu(colors);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("White", 5);
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Quit", 1);
    glutAddMenuEntry("Add a curve", 2);
    glutAddSubMenu("Set curve color", colorMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInitWindowSize(screen_x, screen_y);
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    int fullscreen = 0;
    if (fullscreen)
    {
        glutGameModeString("800x600:32");
        glutEnterGameMode();
    }
    else
    {
        glutCreateWindow("Program 10; Beziers");
    }
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    
    glColor3d(0, 0, 0);
    glClearColor(0.0, 0.0, 0.0, 0);
    InitializeMyStuff();
    
    glutMainLoop();
    
    return 0;
}
