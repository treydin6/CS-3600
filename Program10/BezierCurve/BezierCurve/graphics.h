#include "GLUT/glut.h"

void text_output(float x, float y, char *string);
void DrawCircle(float x1, float y1, float radius);
void DrawRectangle(float x1, float y1, float x2, float y2);
void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

// "Prototypes" of some color variables defined in graphics.cpp
extern GLfloat redMaterial[];
extern GLfloat greenMaterial[];
extern GLfloat brightGreenMaterial[];
extern GLfloat blueMaterial[];
extern GLfloat whiteMaterial[];


class Point2 {
public:
    Point2();
    Point2(double x, double y);
    double getX() const { return x; };
    double getY() const { return y; };
    void setX(double x) { x = x; };
    void setY(double y) { y = y; };
    Point2 operator*(const double &rhs);
    Point2 operator+(const Point2 &rhs);
    
    double x, y;
};



class Bezier {
public:
    Bezier() {}
    Bezier(Point2 p0, Point2 p1, Point2 p2, Point2 p3) {
        points[0] = p0; points[1] = p1; points[2] = p2; points[3] = p3; radius = 5;
    }
    Point2 Evaluate(float t);
    void DrawCurve();
    void DrawControlPoints();
    int IsPicked(float x, float y);
    
    Point2 points[4];
    double color[3];
    int radius = 7;
};
