//
//  maze.hpp
//  Program 5 maze
//
//  Created by Trey Winward on 1/30/20.
//  Copyright © 2020 Trey Winward. All rights reserved.
//

#ifndef maze_h
#define maze_h

const int HEIGHT = 10;
const int WIDTH = 9;

struct Cell {
    Cell();
    void Draw(int x, int y);
    bool left, top, right, bottom, visited;

};

class Maze {
public:
    Maze();
    void RemoveWalls();
    void RemoveWallsR(int i, int j);
    void Draw();
    
private:
    Cell cells[WIDTH][HEIGHT];
};


#endif /* maze_h */
