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
#include "CollisionAware.h"
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

void circle::inversedX(){
    this->dX = -dX;
}

void circle::inversedY(){
    this->dY = -dY;
}

void circle::setdX(double dx){
    this->dX = dx;
}

void circle::setdY(double dy){
    this->dY = dy;
}

void circle::update(double screen_x, double screen_y, int currentBall, std::vector<circle>& mCircles){
    if(getX() + getRadius() + getdX() >= screen_x || getX() - getRadius() + getdX() < 0){
        inversedX();
    }
    if(getY() + getRadius() + getdY() >= screen_y || getY() - getRadius() + getdY() < 0){
        inversedY();
    }
    this->mX += getdX();
    this->mY += getdY();
    
    // state of ball -> ball
    // take out of circle class and make seperate function?
    unsigned int i;
    double x1, y1, r1, x2, y2, r2, distance;
    for(i = currentBall + 1; i < mCircles.size(); i++){
        x1 = getX();
        y1 = getY();
        r1 = getRadius();
        x2 = mCircles[i].getNextX();
        y2 = mCircles[i].getNextY();
        r2 = mCircles[i].getRadius();
        distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        if(distance < r1 + r2){
            Collide(currentBall, i, mCircles);
        }
    }
}

void circle::addGravity(){
    this->dY -= .2;
    this->dY -= .2;
}

void circle::draw(){
    glColor3d(getRed(), getGreen(), getBlue());
    DrawCircle(getX(), getY(), getRadius());
}
