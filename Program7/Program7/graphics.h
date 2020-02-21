//
//  graphics.hpp
//  Program 5 maze
//
//  Created by Trey Winward on 1/30/20.
//  Copyright © 2020 Trey Winward. All rights reserved.
//

#ifndef graphics_h
#define graphics_h
#include "maze.h"
#include "Rat.h"


#pragma once



void DrawLine(double x1, double y1, double x2, double y2);
enum viewtype { top_view, perspective_view, rat_view, move_view };
extern viewtype current_view;
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void setTopView(int height, int width);
void setPerspectiveView(int height, int width);
void setMoveView(int height, int width);

#endif /* graphics_h */
