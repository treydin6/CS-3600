//
//  circle.hpp
//  Program2
//
//  Created by Treydin M. Winward on 1/8/20.
//  Copyright © 2020 Treydin M. Winward. All rights reserved.
//

#ifndef circle_h
#define circle_h

#include <stdio.h>

#endif /* circle_h */

class circle {
public:
    circle();
    circle(double x, double y, double dX, double dY, double radius, double red, double green, double blue);
    double getX();
    double getY();
    double getRadius();
    double getdX();
    double getdY();
    double getRed();
    double getGreen();
    double getBlue();
    void setdX();
    void setdY();
    
    
    double mX, mY, mRadius, dX, dY, mRed, mGreen, mBlue;
    
};
