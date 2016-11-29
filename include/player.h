#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>
#include <map>

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
  enum State {
    running, jumping, idle
  };
  enum Direction {
    left, right
  };

  State current_state;
  State previous_state;

  Direction direction;

  Uint32 next_animation;
  Uint32 last_animation;

  Image spritesheet;

  std::map<Direction, std::map<State, std::vector<Rect>>> sprites;
  Rect sprite;
  int frame;

  int onGround;

  double xv, yv;

  void setState();
  void setDirection();
  void initSprites();
  void selectSprite();

  void move();
  void jump();
  Rect nextSprite();
public:
  int x, y;

  Player(Image s);
  void handleInput(SDL_Event &e);

  void update();

  void draw(Window w);
  void draw(Window w, int cx, int cy);
};

#endif
