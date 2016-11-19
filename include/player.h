#ifndef PLAYER_H_
#define PLAYER_H_

#include "draw.h"

const int SPRITEW = 32;
const int SPRITEH = 64;
const int NBJUMP = 2;

const double XVEL = 4.0;
const double YVEL = 8.0;
const double GRAVITY = 0.5;

class Player
{
private:
public:
  int x, y;
  double xv, yv;
  int onGround;
  Image spritesheet;
  Rect sprite;

  Player(Image s);
  void handleInput(SDL_Event &e);
  void move();
  void jump();
  void draw(SDL_Renderer *renderer);
  void draw(SDL_Renderer *renderer, int cx, int cy);
};

#endif
