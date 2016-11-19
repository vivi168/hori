#include "player.h"

Player::Player(Image s)
{
  x  = 0; y  = 0;
  xv = 0; yv = YVEL;
  jumping = false;
  sprite = Rect(0,0,SPRITEW,SPRITEH);
  spritesheet = s;
}

void Player::handleInput(SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
  //Adjust the velocity
    switch (e.key.keysym.sym) {
      case SDLK_LEFT: xv -= XVEL; break;
      case SDLK_RIGHT: xv += XVEL; break;
      // case SDLK_UP:
      //   if(!jumping) {
      //     jumping = true;
      //     yv = -2*YVEL;
      //   }
      //   break;
    }
  }
  //If a key was released
  else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    //Adjust the velocity
    switch (e.key.keysym.sym) {
      case SDLK_LEFT: xv += XVEL; break;
      case SDLK_RIGHT: xv -= XVEL; break;
      // case SDLK_UP : yv = YVEL; break;
    }
  }
}

void Player::move()
{
  int newx = x + xv;
  int newy = y + yv;

  if ((newx >= 0) && (newx + SPRITEW <= LEVEL_WIDTH))
    x = newx;


  if ((newy >= 0) && (newy + SPRITEH <= LEVEL_HEIGHT))
    y = newy;

  // if (y + SPRITEH == LEVEL_HEIGHT) {
    jumping = false;
  // }

}

void Player::draw(SDL_Renderer *renderer)
{
  spritesheet.drawClip(renderer, sprite, x, y);
}

// relative to camera x,y
void Player::draw(SDL_Renderer *renderer, int cx, int cy)
{
  spritesheet.drawClip(renderer, sprite, x-cx, y-cy);
}

