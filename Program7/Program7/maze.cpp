//
//  maze.cpp
//  Program 5 maze
//
//  Created by Trey Winward on 1/30/20.
//  Copyright © 2020 Trey Winward. All rights reserved.
//
#define GL_SILENCE_DEPRECATION
#include "maze.h"
#include <vector>
#include "GLUT/glut.h"
#include "graphics.h"
#include <iostream>

Cell::Cell(){
    left = top = right = bottom = true;
    visited = false;
}

void Cell::Draw(int x, int y){
    
    
    if (left){
        int red = (x * 374920 + y * 830274) % 256;
        int green = (x * 940274 + y * 340274) % 256;
        int blue = (x * 312947 + y * 826174) % 256;
        glColor3ub(red, green, blue);
        DrawLine(x, y, x, y+1);
        glBegin(GL_QUADS);
        glVertex3i(x, y, 0);
        glVertex3i(x, y + 1, 0);
        glVertex3i(x, y + 1, 1);
        glVertex3i(x, y, 1);
        glEnd();
    }
    if (top){
        int red = (x * 83910 + y * 12583) % 256;
        int green = (x * 36284 + y * 58204) % 256;
        int blue = (x * 29473 + y * 64824) % 256;
        glColor3ub(red, green, blue);
        DrawLine(x, y + 1, x + 1, y + 1);
        glBegin(GL_QUADS);
        glVertex3i(x, y+1, 0);
        glVertex3i(x+1, y+1, 0);
        glVertex3i(x+1, y+1, 1);
        glVertex3i(x, y+1, 1);
        glEnd();
    }
    if (right){
        int red = (x * 82548 + y * 26482) % 256;
        int green = (x * 428493 + y * 96589) % 256;
        int blue = (x * 648485 + y * 1726490) % 256;
        glColor3ub(red, green, blue);
        DrawLine(x + 1, y + 1, x + 1, y);
        glBegin(GL_QUADS);
        glVertex3i(x+1, y, 0);
        glVertex3i(x+1, y, 1);
        glVertex3i(x+1, y+1, 1);
        glVertex3i(x+1, y+1, 0);
        glEnd();
    }
    if (bottom){
        int red = (x * 2365247 + y * 976235) % 256;
        int green = (x * 55427356 + y * 95327) % 256;
        int blue = (x * 354573784 + y * 73784) % 256;
        glColor3ub(red, green, blue);
        DrawLine(x + 1, y, x, y);
        glBegin(GL_QUADS);
        glVertex3i(x, y, 0);
        glVertex3i(x+1, y, 0);
        glVertex3i(x+1, y, 1);
        glVertex3i(x, y, 1);
        glEnd();
    }
}


Maze::Maze(){}

void Maze::RemoveWalls(){
    RemoveWallsR(0, 0);
    // remove top and bottom wall.. start and finish? random?
}

void Maze::RemoveWallsR(int i, int j){
    cells[i][j].visited = true;
    cells[0][0].bottom = false;
    cells[WIDTH-1][HEIGHT-1].top = false;
    
    
    while(true){
        enum MOVES {LEFT, UP, RIGHT, DOWN };
        std::vector<MOVES> moves;
        
        
        if(i - 1 >= 0 && !cells[i -1][j].visited){
            moves.push_back(LEFT);
        }
        
        if(i + 1 < WIDTH && !cells[i + 1][j].visited){
            moves.push_back(RIGHT);
        }
        
        if(j - 1 >= 0 && !cells[i][j - 1].visited){
            moves.push_back(DOWN);
        }
        
        if(j + 1 < HEIGHT && !cells[i][j + 1].visited){
            moves.push_back(UP);
        }
        
        if(moves.size() == 0){
            return;
        }
        
        int r = rand() % moves.size();
        if(moves[r] == LEFT) {
            cells[i][j].left = false;
            cells[i - 1][j].right = false;
            RemoveWallsR(i - 1, j);
        }
        
        if(moves[r] == UP){
            cells[i][j].top = false;
            cells[i][j + 1].bottom = false;
            RemoveWallsR(i, j + 1);
        }
        
        if(moves[r] == RIGHT) {
            cells[i][j].right = false;
            cells[i + 1][j].left = false;
            RemoveWallsR(i+1, j);
        }
        
        if(moves[r] == DOWN){
            cells[i][j].bottom = false;
            cells[i][j - 1].top = false;
            RemoveWallsR(i, j - 1);
        }
    }
}

void Maze::Draw(){
    int x, y;
    for(x = 0; x < WIDTH; x++){
        for(y = 0; y < HEIGHT; y++){
            cells[x][y].Draw(x, y);
        }
    }
}

bool Maze::isSafeToMove(double x, double y, double size){
    int i = (int)x;
    int j = (int)y;
    double Xoffset = x - i;
    double Yoffset = y - j;
    // check running into walls
    if(cells[i][j].right && Xoffset + size > 1.0){
        return false;
    }
    if(cells[i][j].left && Xoffset - size < 0.0){
        return false;
    }
    if(cells[i][j].top && Yoffset + size > 1.0){
        return false;
    }
    if(cells[i][j].bottom && Yoffset - size < 0.0){
        return false;
    }
    // check running into corners
    if(Xoffset + size > 1.0 && Yoffset + size > 1.0){
        return false;
    }
    if(Xoffset - size < 0.0 && Yoffset - size < 0.0){
        return false;
    }
    if(Xoffset + size > 1.0 && Yoffset - size < 0.0){
        return false;
    }
    if(Xoffset - size < 0.0 && Yoffset + size > 1.0){
        return false;
    }
    
    return true;
    
}


