#ifndef PLAYER_H_
#define PLAYER_H_

#include "draw.h"

const int SPRITEW = 32;
const int SPRITEH = 64;
const int XVEL = 4;
const int YVEL = 4;

class Player
{
private:
public:
  int x, y;
  int xv, yv;
  bool jumping;
  Image spritesheet;
  Rect sprite;

  Player(Image s);
  void handleInput(SDL_Event &e);
  void move();
  void draw(SDL_Renderer *renderer);
  void draw(SDL_Renderer *renderer, int cx, int cy);
};

#endif
