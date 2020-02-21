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
    glColor3d(0, 0, 0);
    if (left){
        DrawLine(x, y, x, y + 1);
    }
    if (top){
        DrawLine(x, y + 1, x + 1, y + 1);
    }
    if (right){
        DrawLine(x + 1, y + 1, x + 1, y);
    }
    if (bottom){
        DrawLine(x + 1, y, x, y);
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


