#include <iostream>
#include <fstream>
#include <sstream>
#include "map.h"

Tile::Tile()
{
  flags = 0x00;
}

Tile::Tile(int x, int y, int f)
{
  int img_no = f & 0xff;
  hitbox = Rect(x, y, TILEW, TILEH);
  img = Rect(img_no*TILEW, 0, TILEW, TILEH);
  flags = f >> 8;
  tno = img_no;
}

int Tile::x() { return hitbox.x(); }
int Tile::y() { return hitbox.y(); }

Map::Map(std::string data_path, Image b, Image t)
{
  bg = b;
  tileset = t;
  std::ifstream file(data_path);
  std::string line;
  int i = 0, j = 0;

  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::vector<Tile> tmp;
    int value;

    while (stream >> std::hex >> value) {
      tmp.push_back(Tile(j*TILEW, i*TILEH, value));
      j++;
    }
    tiles.push_back(tmp);
    i++;
    j = 0;
  }
}

void Map::draw(Window w, int cx, int cy)
{
  bg.drawClip(w, Rect(0,0,1280,800), 0-cx, 0-cy);
  for (int i = 0; i < tiles.size(); i ++) {
    for (int j = 0; j < tiles[i].size(); j ++) {
      tileset.drawClip(w, tiles[i][j].img, tiles[i][j].x()-cx, tiles[i][j].y()-cy);
    }
  }
}
