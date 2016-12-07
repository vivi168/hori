#include "player.h"
#include <iostream>

Player::Player(Image s)
{
  x  = 0; y = 0;
  xv = 0.0; yv = 0.0; jv = 0.0;
  onGround = 2;

  next_animation = 0;
  last_animation = 0;
  frame = 0;
  current_state = idle;
  previous_state = current_state;
  direction = right;

  spritesheet = s;

  initSprites();
}

void Player::initSprites()
{
  sprites[left][idle] = {
    Rect(SPRITEW*3,0,SPRITEW,SPRITEH)
  };
  sprites[left][running] = {
    Rect(SPRITEW*0,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*1,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*2,0,SPRITEW,SPRITEH)
  };
  sprites[left][jumping] = {
    Rect(SPRITEW*8,0,SPRITEW,SPRITEH)
  };

  sprites[right][idle] = {
    Rect(SPRITEW*4,0,SPRITEW,SPRITEH)
  };
  sprites[right][running] = {
    Rect(SPRITEW*5,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*6,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*7,0,SPRITEW,SPRITEH)
  };
  sprites[right][jumping] = {
    Rect(SPRITEW*9,0,SPRITEW,SPRITEH)
  };
}

void Player::handleInput(SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        xv -= XVEL;
        break;
      case SDLK_RIGHT:
        xv += XVEL;
        break;
      case SDLK_SPACE:
        jump();
        break;
    }
    keypressed[e.key.keysym.sym] = true;
  }
  else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        xv += XVEL;
        break;
      case SDLK_RIGHT:
        xv -= XVEL;
        break;
    }
    keypressed[e.key.keysym.sym] = false;
  }
}

void Player::setState()
{
  previous_state = current_state;
  if (xv == 0)
    current_state = idle;
  if (xv < 0 or xv > 0)
    current_state = running;
  if(onGround > 0)
    current_state = jumping;
}

void Player::setDirection() {
  if (xv > 0) {
    direction = right;
  }
  if (xv < 0) {
    direction = left;
  }
}

void Player::move()
{
  if (current_state == jumping)
    x += jv;
  else
    x += xv;
  y += yv;

  // should also check if touches blocking tile
  if ((x < 0) || (x + SPRITEW > LEVEL_WIDTH)) {
    x -= xv;
  }

  // should also check if touches blocking tile
  if (y + SPRITEH > LEVEL_HEIGHT) {
    y = LEVEL_HEIGHT-SPRITEH;
    yv = 0;
    onGround = 0;
    jv = 0;
  } else {
    if (yv < YVEL)
      yv += GRAVITY;
  }
}

void Player::jump()
{
  if (onGround < NBJUMP) {
    yv = -YVEL;
    onGround += 1;
    jv = 0;
    if (keypressed[SDLK_LEFT])
      jv = -XVEL;
    else if (keypressed[SDLK_RIGHT])
      jv = XVEL;
  }
}

Rect Player::nextSprite()
{
  if (previous_state != current_state)
    frame = 0;
  else {
    frame ++;
    if (frame >= sprites[direction][current_state].size())
        frame = 0;
  }

  return sprites[direction][current_state][frame];
}

void Player::selectSprite()
{
  next_animation = SDL_GetTicks();
  if (next_animation - last_animation > ANIMATION_SPEED or
      previous_state != current_state) {

    last_animation = next_animation;

    sprite = nextSprite();
  }
}

void Player::update()
{
  setState();
  setDirection();
  selectSprite();

  move();
}

void Player::draw(Window w)
{
  spritesheet.drawClip(w, sprite, x, y);
}

// relative to camera x,y
void Player::draw(Window w, int cx, int cy)
{
  spritesheet.drawClip(w, sprite, x-cx, y-cy);
}

