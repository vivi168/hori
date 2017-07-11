#pragma once

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
    Tile(int, int, int);

    int x();
    int y();
};

class TileMap
{
  private:
    Image bg;
    Image tileset;
    std::vector<std::vector<Tile>> tiles;
  public:
    TileMap(std::string, Image, Image);
    void draw(Window, int, int);
};
