#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>

#include "draw.h"
#include "rect.h"

const int TILEW = 32;
const int TILEH = 32;

class Tile
{
private:
  Rect hitbox;
  int flags;
public:
  Rect img;
  int tno;

  Tile();
  Tile(int x, int y, int f);

  int x();
  int y();
};

class Map
{
private:
  Image bg;
  Image tileset;
  std::vector<std::vector<Tile>> tiles;
public:
  Map(std::string path, Image b, Image t);
  void draw(Window w, int cx, int cy);
};

#endif
