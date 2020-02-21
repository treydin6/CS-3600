//
//  rat.hpp
//  mazeWithRat
//
//  Created by Trey Winward on 2/5/20.
//  Copyright © 2020 Trey Winward. All rights reserved.
//

#ifndef rat_h
#define rat_h
#include "graphics.h"
#include <GLUT/glut.h>
#include <iostream>
#include <cmath>

class Rat{
public:
    Rat();
    Rat( double x, double y, double radius, double speed, double degrees);
    double getX();
    double getY();
    double getRadius();
    double getSpeed();
    double getDegrees();
    
    void setX(double x);
    void setY(double y);
    void setRadius(double radius);
    void setSpeed(double speed);
    void setDegrees(double degrees);
    
    void spinLeft();
    void spinRight();
    void scurryForward();
    void powerScurry();
    
    void draw();
    
private:
    double mX, mY, mRadius, mSpeed, mDegrees;
};

#endif /* rat_h */
