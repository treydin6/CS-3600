//
//  rat.cpp
//  mazeWithRat
//
//  Created by Trey Winward on 2/5/20.
//  Copyright © 2020 Trey Winward. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "rat.h"

Rat::Rat(){
    
}

Rat::Rat(double x, double y, double radius, double speed, double degrees)
:mX(x), mY(y), mRadius(radius), mSpeed(speed), mDegrees(degrees){
    
}

double Rat::getX(){
    return this->mX;
}

double Rat::getY(){
    return this->mY;
}

double Rat::getRadius(){
    return this->mRadius;
}

double Rat::getSpeed(){
    return this->mSpeed;
}

double Rat::getDegrees(){
    return this->mDegrees;
}

void Rat::setX(double x){
    this->mX = x;
}

void Rat::setY(double y){
    this->mY = y;
}

void Rat::setRadius(double radius){
    this->mRadius = radius;
}

void Rat::setSpeed(double speed){
    this->mSpeed = speed;
}

void Rat::setDegrees(double degrees){
    this->mDegrees = degrees;
}

void Rat::spinLeft(){
    double current = getDegrees();
    setDegrees(current + 4);
    //mDegrees += 4;
}

void Rat::spinRight(){
    double current = getDegrees();
    setDegrees(current -4) ;
}

void Rat::scurryForward(){
    
    double radians = getDegrees() * 3.1415926 / 180.;
    double dX = std::cos(radians);
    double dY = std::sin(radians);
    double nextX = getX();
    double nextY = getY();
    nextX += dX * getSpeed();
    nextY += dY * getSpeed();
    this->mX += dX * getSpeed();
    this->mY += dY * getSpeed();
    
}

void Rat::powerScurry(){
    double radians = getDegrees() * 3.1415926 / 180.;
    double dX = std::cos(radians);
    double dY = std::sin(radians);
    double nextX = getX();
    double nextY = getY();
    nextX += dX * getSpeed();
    nextY += dY * getSpeed();
    this->mX += dX * (getSpeed() + .1);
    this->mY += dY * (getSpeed() + .1);
}

void Rat::draw(){
    if(current_view == rat_view){
        return;
    }else{
        glColor3d(1, 0, 0);
        glPushMatrix();
        glTranslated(this->getX(), this->getY(), getZ(this->getX(), this->getY()) + 0.1);
        glRotated(getDegrees(), 0, 0, 1);
        glScaled(.5, .5, 1.0);
        DrawTriangle(.2, 0, -0.2, 0.2, -0.2, -0.2);
        glPopMatrix();
    }
}
