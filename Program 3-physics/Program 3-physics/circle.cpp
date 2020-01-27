//
//  circle.cpp
//  Program3
//
//  Created by Treydin M. Winward on 1/8/20.
//  Copyright © 2020 Treydin M. Winward. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "circle.h"
#include "graphics.h"
#include <GLUT/glut.h>
#include <iostream>
#include "collide.h"

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

void circle::inverseDX(){
    this->dX = -dX;
}
void circle::inverseDY(){
    this->dY = -dY;
}

void circle::setdX(double dx){
    this->dX = dx;
}

void circle::setdY(double dy){
    this->dY = dy;
}

void circle::setGravity(){
    this->dY -= .2;
}

void circle::update(double screen_x, double screen_y, std::vector<circle>& circles, int currentBall){
    if(getX() + getRadius() + getdX() >= screen_x || getX() - getRadius() + getdX() < 0){
        inverseDX();
    }
    if(getY() + getRadius() + getdY() >= screen_y || getY() - getRadius() + getdY() < 0){
        inverseDY();
    }
    
    // check ball to ball collision
    unsigned int i;
    double x1, y1, radius1, x2, y2, radius2, distance;
    for(i = currentBall + 1; i < circles.size(); i++){
        x1 = getNextX();
        y1 = getNextY();
        radius1 = getRadius();
        x2 = circles[i].getNextX();
        y2 = circles[i].getNextY();
        radius2 = circles[i].getRadius();
        distance = sqrt( (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
        if(distance < radius1 + radius2){
            Collide(currentBall, i, circles);
        }
    }
    this->mX += getdX();
    this->mY += getdY();
}

void circle::draw(){
    glColor3d(getRed(), getGreen(), getBlue());
    DrawCircle(getX(), getY(), getRadius());
}
