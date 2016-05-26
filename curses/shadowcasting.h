#ifndef SHADOWCASTING_H_INCLUDED
#define SHADOWCASTING_H_INCLUDED
#include "tile.h"
#include <vector>
#include <math.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "actor.h"

static int multipliers[4][8] = {
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

void cast_light(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, unsigned int x, unsigned int y, int, int, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy, sf::RenderWindow &window, sf::RenderStates &renderState);

void castShadow(std::vector<std::vector<std::vector<tile*> > > *&_map, std::vector<item*> &localItems, unsigned int x, unsigned int y, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy, sf::RenderWindow &window, sf::RenderStates &renderState, float intensity, float decreaseBy);

std::vector<coordinate> findEnemies(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems, unsigned int x, unsigned int y, unsigned int radius, unsigned int row,
                float start_slope, float end_slope, unsigned int xx, unsigned int xy, unsigned int yx, unsigned int yy);

void do_fov(std::vector<std::vector<std::vector<tile*> > > &_map, std::vector<item*> &localItems,  unsigned int x, unsigned int y, int, int, unsigned int radius, sf::RenderWindow &window, sf::RenderStates &renderState, bool castingLight, float intensity, float decreaseBy);
void do_fov(std::vector<std::vector<std::vector<tile*> > > *&_map, std::vector<item*> &localItems,  unsigned int x, unsigned int y, unsigned int radius, sf::RenderWindow &window, sf::RenderStates &renderState, bool castingLight, float intensity, float decreaseBy);
std::vector<coordinate> findEnemiesAtAngle(short direction, std::vector<std::vector<std::vector<tile*> > >&_map, unsigned int x, unsigned int y, unsigned int radius);
#endif // SHADOWCASTING_H_INCLUDED
