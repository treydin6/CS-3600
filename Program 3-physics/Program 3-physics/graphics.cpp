// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//        and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#define GL_SILENCE_DEPRECATION
#include <cmath>
#include <cstring>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <OpenGL/OpenGL.h>
#include <iostream>
#include <vector>
#include <string>
#include "circle.h"
#include "graphics.h"
//#include <srand>



// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;

// Vector to store circle objects;
std::vector<circle> circles;

//
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
    glBegin(GL_POLYGON);
    for(int i=0; i<32; i++)
    {
        double theta = (double)i/32.0 * 2.0 * 3.1415926;
        double x = x1 + radius * cos(theta);
        double y = y1 + radius * sin(theta);
        glVertex2d(x, y);
    }
    glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
    glBegin(GL_QUADS);
    glVertex2d(x1,y1);
    glVertex2d(x2,y1);
    glVertex2d(x2,y2);
    glVertex2d(x1,y2);
    glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
    void *font = GLUT_BITMAP_9_BY_15;
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    int len, i;
    glRasterPos2d(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
    
    glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    int i = 0;
    for(i = 0; i < circles.size(); i++){
        circles[i].update(screen_x, screen_y, circles, i);
        circles[i].setGravity();
        circles[i].draw();
    }
    
    glutSwapBuffers();
    glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
    switch (c)
    {
        case 27: // escape character means to quit the program
            exit(0);
            break;
        case 'b':
            // do something when 'b' character is hit.
            break;
        default:
            return; // if we don't care, return without glutPostRedisplay()
    }
    
    glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
    // Reset our global variables to the new width and height.
    screen_x = w;
    screen_y = h;
    
    // Set the pixel resolution of the final picture (Screen coordinates).
    glViewport(0, 0, w, h);
    
    // Set the projection mode to 2D orthographic, and set the world coordinates:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        exit(0);
    }
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
    {
    }
    glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
    int numCircles;
    bool didFind = false;
    unsigned int j;
    double x1, y1, radius1, distance;
    std::cout << "How many Circles do you want? " << std::endl;
    std::cin >> numCircles;
    srand(time(NULL));
    
    while(circles.size() < numCircles){
        double radius = rand() % 50 + 25;
        double x = rand() % 600 + radius;
        double y = rand() % 400 + radius;
        
        double dX = rand() % 5 + .5;
        double dY = rand() % 3 + .3;
        double red = rand() % 101 / 100.;
        double green = rand() % 101 / 100.;
        double blue = rand() % 101 / 100.;
        circle NewCircle(x, y, dX, dY, radius, red, green, blue);
        if(circles.size() > 0){
            for(j = 0; j < circles.size(); j++){
                x1 = circles[j].getX();
                y1 = circles[j].getY();
                radius1 = circles[j].getRadius();
                distance = sqrt( (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) );
                if(distance > radius + radius1){
                    didFind = false;
                } else{
                    didFind = true;
                    break;
                }
            }
            if(didFind == false){
                circles.push_back(NewCircle);
            }
        } else{
            circles.push_back(NewCircle);
        }
    }
}


int main(int argc, char **argv)
{
    
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screen_x, screen_y);
    glutInitWindowPosition(50, 50);
    
    int fullscreen = 0;
    if (fullscreen)
    {
        glutGameModeString("800x600:32");
        glutEnterGameMode();
    }
    else
    {
        glutCreateWindow("Program 3: Treydin Winward");
    }
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    
    glColor3d(0,0,0); // forground color
    glClearColor(1, 1, 1, 0); // background color
    InitializeMyStuff();
    
    glutMainLoop();
    
    return 0;
}

