//
//  circle.cpp
//  Program2
//
//  Created by Treydin M. Winward on 1/8/20.
//  Copyright © 2020 Treydin M. Winward. All rights reserved.
//

#include "circle.h"

circle::circle(){}

circle::circle(double x, double y, double deltaX, double deltaY, double radius, double red, double green, double blue){
    mX = x;
    mY = y;
    dX = deltaX;
    dY = deltaY;
    mRadius = radius;
    mRed = red;
    mGreen = green;
    mBlue = blue;
}

double circle::getX(){
    return this->mX;
}

double circle::getY(){
    return this->mY;
}

double circle::getRadius(){
    return this->mRadius;
}

double circle::getRed(){
    return this->mRed;
}

double circle::getGreen(){
    return this->mGreen;
}

double circle::getBlue(){
    return this->mBlue;
}

double circle::getdX(){
    return this->dX;
}

double circle::getdY(){
    return this->dY;
}

void circle::setdX(){
    this->dX = -dX;
}
void circle::setdY(){
    this->dY = -dY;
}
