#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "menu.h"
#include "aStar.h"
#include "tile.h"

class actor
{
protected:
    char _symbol;
    int x,y;
public:
    bool controlled;
    int row(){return y;}
    int col(){return x;}

    char symbol(){return _symbol;}
    void pos(int _y,int _x){x=_x;y=_y;}
};

class player : public actor
{
public:
    void movement(std::vector<std::vector<tile> >, char);
    player();
};

class monster : public actor
{
    coordinate memory;
    std::vector<coordinate> path;
public:
    int speed;
    int counter;
    bool musttouch;
    void aiMovement(std::vector<std::vector<tile> >, coordinate, std::vector<actor>);

    monster(int,char);
};

#endif // ACTOR_H_INCLUDED
