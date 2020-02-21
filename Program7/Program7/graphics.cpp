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
#include "GLUT/glut.h"
#include "graphics.h"

#include <stdlib.h>
#include <iostream>

// CONTROLS
//    p perspective view
//    r Rat view
//    t Top view
//    m Move with rat view
//    s sudo rat


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;

bool LeftClick = false;
bool RightClick = false;
bool MiddleClick = false;
bool power = false;

viewtype current_view = rat_view;

Maze gMaze;
// grat(x, y, r, speed degrees
Rat gRat(.5, .5, .2, .03, 90);


//
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
    glBegin(GL_TRIANGLE_STRIP);
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

void DrawLine(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(current_view == perspective_view){
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        gluLookAt(-3,-3,7,  3,3,0,  0,0,1);
    } else if(current_view == top_view){
        glDisable(GL_DEPTH_TEST);
        glLoadIdentity();
    } else if(current_view == move_view){
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        gluLookAt(gRat.getX(), gRat.getY() -3, 10,   gRat.getX(),gRat.getY(),0,  0,0,1);
    } else{ // current_view == rat_view
        glEnable(GL_DEPTH_TEST);
        glLoadIdentity();
        double z_level = .25;
        double x = gRat.getX();
        double y = gRat.getY();
        double radians = gRat.getDegrees() * 3.1415926 / 180.;
        double dX = std::cos(radians);
        double dY = std::sin(radians);
        double at_x = x + dX;
        double at_y = y + dY;
        double at_z = z_level;
        gluLookAt(x,y,z_level,  at_x,at_y,at_z,  0,0,1);
        
    }
    // Update the rat
    if(LeftClick == true){
        gRat.spinLeft();
    }
    if(MiddleClick){
        gRat.scurryForward();
    }
    if(RightClick == true){
        gRat.spinRight();
    }
    if(power){
        if(LeftClick){
            gRat.spinLeft();
        }
        if(MiddleClick){
            gRat.powerScurry();
        }
        if(RightClick){
            gRat.spinRight();
        }
    }
    
    //glColor3ub(100,100,255);
    gMaze.RemoveWalls();
    gMaze.Draw();
    gRat.draw();
    
    if(current_view != rat_view){
        gRat.draw();
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
        case 'p':
            current_view = perspective_view;
            setPerspectiveView(screen_x, screen_y);
            break;
        case 'r':
            current_view = rat_view;
            setPerspectiveView(screen_x, screen_y);
            break;
        case 't':
            current_view = top_view;
            setTopView(screen_x, screen_y);
            break;
        case 'm':
            current_view = move_view;
            setMoveView(screen_x, screen_y);
            break;
        case 's':
            power = !power;
        default:
            return; // if we don't care, return without glutPostRedisplay()
    }
    
    glutPostRedisplay();
}

// Notes from class to set different view for the rat.

// Going into 2-D mode, view from the top of the maze
void setTopView(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double world_margin_x = 0.5;
    double world_margin_y = 0.5;
    gluOrtho2D(-world_margin_x, WIDTH + world_margin_x, -world_margin_y, HEIGHT + world_margin_y);
    glMatrixMode(GL_MODELVIEW);
}

// seeing the rat and maze from a distance.
void setPerspectiveView(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspectRatio = (GLdouble)width / (GLdouble)height;
    //gluPerspective(field of View, aspectRatio, Z near, Z far);
    gluPerspective(38.0, aspectRatio, .1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void setMoveView(int width, int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspectRatio = (GLdouble)width / (GLdouble)height;
    //gluPerspective(field of View, aspectRatio, Z near, Z far);
    gluPerspective(38.0, aspectRatio, .1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int width, int height)
{
    // Reset our global variables to the new width and height.
    screen_x = width;
    screen_y = height;
    
    // Set the pixel resolution of the final picture (Screen coordinates).
    glViewport(0, 0, width, height);
    
    if(current_view == top_view){
        setTopView(width, height);
    } else if(current_view == perspective_view){
        setPerspectiveView(width, height);
    } if(current_view == move_view){
        setMoveView(width, height);
    } else {
        setPerspectiveView(width, height);
    }
    
    // Set the projection mode to 2D orthographic, and set the world coordinates:
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    const double MARGIN = 0.5;
//    gluOrtho2D(-MARGIN, WIDTH+MARGIN, -MARGIN, HEIGHT+MARGIN);
//    glMatrixMode(GL_MODELVIEW);
    
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        LeftClick = true;
    }
    if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        LeftClick = false;
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        MiddleClick = true;
    }
    if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
    {
        MiddleClick = false;
    }
    if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        RightClick = true;
    }
    if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        RightClick = false;
    }
    
    glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
        glutCreateWindow("Program 7: Rat 3-D");
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


// on midtrem. (3-d)
//gluLookAt(x, y, z, 3, 3, 0, 0, 0, 1)
//first three are where the camera view starts
//next 3 where you want to look
//last three look up on camera-- spins camera
