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

  int frame;
  int dir;

  Image spritesheet;
  Rect sprite;
  Rect sprites[10];

  Player(Image s);
  void handleInput(SDL_Event &e);
  void move();
  void jump();
  void selectSprite(int frame);
  void draw(Window w);
  void draw(Window w, int cx, int cy);
};

#endif
