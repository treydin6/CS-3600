//
//  circle.hpp
//  Program2
//
//  Created by Treydin M. Winward on 1/8/20.
//  Copyright © 2020 Treydin M. Winward. All rights reserved.
//

#ifndef circle_h
#define circle_h
#include <vector>
#include "circle.h"
//#include "collide.h"
#include <cmath>



class circle {
public:
    circle();
    circle(double x, double y, double dX, double dY, double radius, double red, double green, double blue);
    double getX();
    double getY();
    double getRadius();
    double getNextX();
    double getNextY();
    double getdX();
    double getdY();
    double getRed();
    double getGreen();
    double getBlue();
    
    void inverseDX();
    void inverseDY();
    void setdX(double dx);
    void setdY(double dy);
    void setGravity();
    
    void update(double screen_X, double scrren_Y, std::vector<circle>& circles, int currentBall);
    void draw();
    
private:
    double mX, mY, mRadius, dX, dY, mRed, mGreen, mBlue;
    
};
#endif /* circle_h */
