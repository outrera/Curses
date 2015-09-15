#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <iostream>
#include <fstream>

class coordinate
{
public:
    int x,y;
    coordinate(int,int);
    coordinate();
};

class dungeon
{
private:
    coordinate directions[4]={coordinate(0,-1),coordinate(1,0),coordinate(0,1),coordinate(-1,0)};
    coordinate mazeBegin;
    int w,h;
public:
    std::vector<std::vector<bool> > dungeon_grid;
    dungeon();
    void hallwayMaker();
};


#endif // DUNGEON_H_INCLUDED
