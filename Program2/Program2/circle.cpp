//
//  circle.cpp
//  Program2
//
//  Created by Treydin M. Winward on 1/8/20.
//  Copyright © 2020 Treydin M. Winward. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "circle.h"
#include "program2.h"
#include <GLUT/glut.h>

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

double circle::getNextX(){
    return this->mX + this->dX;
}

double circle::getNextY(){
    return this-> mY + this->dY;
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

void circle::update(double screen_x, double screen_y){
    if(getX() + getRadius() + getdX() >= screen_x || getX() - getRadius() + getdX() < 0){
        setdX();
    }
    if(getY() + getRadius() + getdY() >= screen_y || getY() - getRadius() + getdY() < 0){
        setdY();
    }
    this->mX += getdX();
    this->mY += getdY();
}

void circle::draw(){
    glColor3d(getRed(), getGreen(), getBlue());
    DrawCircle(getX(), getY(), getRadius());
}
