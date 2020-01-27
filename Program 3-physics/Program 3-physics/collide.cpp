
// Collision handling code, for CS 3600 project 3, January, 2002.
// Bart Stander.

#include "collide.h"
#include <math.h>

const double COLLISION_FRICTION = 1.0;


struct vectortype
{
    double x;
    double y;
};

void Collide(int p1, int p2, std::vector<circle>& particles)
{
    vectortype en; // Center of Mass coordinate system, normal component
    vectortype et; // Center of Mass coordinate system, tangential component
    vectortype u[2]; // initial velocities of two particles
    vectortype um[2]; // initial velocities in Center of Mass coordinates
    double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
    double umn[2]; // initial velocities in Center of Mass coordinates, normal component
    vectortype v[2]; // final velocities of two particles
    double m[2];    // mass of two particles
    double M; // mass of two particles together
    vectortype V; // velocity of two particles together
    double size;
    int i;
    
    double xdif=particles[p1].getNextX() - particles[p2].getNextX();
    double ydif=particles[p1].getNextY() - particles[p2].getNextY();
    
    // set Center of Mass coordinate system
    size=sqrt(xdif*xdif + ydif*ydif);
    xdif/=size; ydif/=size; // normalize
    en.x=xdif;
    en.y=ydif;
    et.x=ydif;
    et.y=-xdif;
    
    // set u values
    u[0].x=particles[p1].getdX();
    u[0].y=particles[p1].getdY();
    m[0]=particles[p1].getRadius()*particles[p1].getRadius();
    u[1].x=particles[p2].getdX();
    u[1].y=particles[p2].getdY();
    m[1]=particles[p2].getRadius()*particles[p2].getRadius();
    
    // set M and V
    M=m[0]+m[1];
    V.x=(u[0].x*m[0] + u[1].x*m[1])/M;
    V.y=(u[0].y*m[0] + u[1].y*m[1])/M;
    
    // set um values
    um[0].x=m[1]/M * (u[0].x-u[1].x);
    um[0].y=m[1]/M * (u[0].y-u[1].y);
    um[1].x=m[0]/M * (u[1].x-u[0].x);
    um[1].y=m[0]/M * (u[1].y-u[0].y);
    
    // set umt and umn values
    for(i=0;i<2;i++)
    {
        umt[i] = um[i].x * et.x + um[i].y * et.y;
        umn[i] = um[i].x * en.x + um[i].y * en.y;
    }
    
    // set v values
    for(i=0;i<2;i++)
    {
        v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
        v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
    }
    
    // reset particle values
    particles[p1].setdX(v[0].x*COLLISION_FRICTION);
    particles[p1].setdY(v[0].y*COLLISION_FRICTION);
    particles[p2].setdX(v[1].x*COLLISION_FRICTION);
    particles[p2].setdY(v[1].y*COLLISION_FRICTION);
    
} /* Collide */
