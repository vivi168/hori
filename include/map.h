#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>

#include "draw.h"
#include "rect.h"

const int TILEW = 32;
const int TILEH = 32;

const int BLOCK_TOP = 0x1;
const int BLOCK_BOT = 0x2;
const int BLOCK_RGT = 0x4;
const int BLOCK_LFT = 0x8;
const int BLOCK_ALL = 0xf;

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
