#include "player.h"
#include <iostream>

Player::Player(Image s)
{
  x  = 0; y = 0;
  xv = 0.0; yv = 0.0;
  onGround = 2;

  next_animation = 0;
  last_animation = 0;

  frame = 0;
  changed_direction = false;
  direction = "right";

  spritesheet = s;

  initSprites();
}

void Player::initSprites()
{
  spritelist["left"]["idle"] = {
    Rect(SPRITEW*3,0,SPRITEW,SPRITEH)
  };
  spritelist["left"]["running"] = {
    Rect(SPRITEW*0,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*1,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*2,0,SPRITEW,SPRITEH)
  };
  spritelist["left"]["jumping"] = {
    Rect(SPRITEW*8,0,SPRITEW,SPRITEH)
  };

  spritelist["right"]["idle"] = {
    Rect(SPRITEW*4,0,SPRITEW,SPRITEH)
  };
  spritelist["right"]["running"] = {
    Rect(SPRITEW*5,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*6,0,SPRITEW,SPRITEH),
    Rect(SPRITEW*7,0,SPRITEW,SPRITEH)
  };
  spritelist["right"]["jumping"] = {
    Rect(SPRITEW*9,0,SPRITEW,SPRITEH)
  };
}

void Player::handleInput(SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        xv -= XVEL;
        setDirection();
        break;
      case SDLK_RIGHT:
        xv += XVEL;
        setDirection();
        break;
      case SDLK_SPACE:
        jump();
        break;
    }
  }
  else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:
        xv += XVEL;
        setDirection();
        break;
      case SDLK_RIGHT:
        xv -= XVEL;
        setDirection();
        break;
    }
  }
}

void Player::move()
{
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
  }
}

void Player::setDirection() {
  changed_direction = true;
  frame = 0;
  if (xv > 0) {
    direction = "right";
  }
  if (xv < 0) {
    direction = "left";
  }
}

int Player::nextFrame()
{
  frame ++;
  if (frame >= spritelist[direction]["running"].size())
    frame = 0;

  return frame;
}

void Player::selectSprite()
{
  bool animate = false;
  next_animation = SDL_GetTicks();
  if (next_animation - last_animation > ANIMATION_SPEED) {
    last_animation = next_animation;
    animate = true;
  }

  if (xv == 0) {
    current_sprite = spritelist[direction]["idle"][0];
  } else {
    if (animate or changed_direction) {
      if (changed_direction) {;
        changed_direction = false;
        current_sprite = spritelist[direction]["running"][frame];
      } else {
        current_sprite = spritelist[direction]["running"][nextFrame()];
      }
    }
  }

  if (onGround > 0) {
    current_sprite = spritelist[direction]["jumping"][0];
  }

}

void Player::draw(Window w)
{
  spritesheet.drawClip(w, current_sprite, x, y);
}

// relative to camera x,y
void Player::draw(Window w, int cx, int cy)
{
  spritesheet.drawClip(w, current_sprite, x-cx, y-cy);
}

