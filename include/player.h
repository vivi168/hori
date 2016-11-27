#ifndef PLAYER_H_
#define PLAYER_H_

#include "draw.h"

const int SPRITEW = 32;
const int SPRITEH = 64;
const int NBJUMP = 2;

const double XVEL = 4.0;
const double YVEL = 8.0;
const double GRAVITY = 0.5;

const Uint32 ANIMATION_SPEED = 100;

class Player
{
private:
  int frame;
  int direction;
  bool changed_direction;
  bool going_right;

  Uint32 next_animation;
  Uint32 last_animation;

  Image spritesheet;
  Rect sprites[10];

  int onGround;

  double xv, yv;

  void setDirection();
public:
  int x, y;

  Player(Image s);
  void handleInput(SDL_Event &e);
  void move();
  void jump();

  void selectSprite();
  void draw(Window w);
  void draw(Window w, int cx, int cy);
};

#endif
