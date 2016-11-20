#include "player.h"

Player::Player(Image s)
{
  x  = 0; y = 0;
  xv = 0.0; yv = 0.0;
  onGround = 2;

  frame = 4;
  dir = 0;

  spritesheet = s;

  sprites[0] = Rect(SPRITEW*0,0,SPRITEW,SPRITEH);
  sprites[1] = Rect(SPRITEW*1,0,SPRITEW,SPRITEH);
  sprites[2] = Rect(SPRITEW*2,0,SPRITEW,SPRITEH);
  sprites[3] = Rect(SPRITEW*3,0,SPRITEW,SPRITEH);
  sprites[4] = Rect(SPRITEW*4,0,SPRITEW,SPRITEH);
  sprites[5] = Rect(SPRITEW*5,0,SPRITEW,SPRITEH);
  sprites[6] = Rect(SPRITEW*6,0,SPRITEW,SPRITEH);
  sprites[7] = Rect(SPRITEW*7,0,SPRITEW,SPRITEH);
  sprites[8] = Rect(SPRITEW*8,0,SPRITEW,SPRITEH);
  sprites[9] = Rect(SPRITEW*9,0,SPRITEW,SPRITEH);
}

void Player::handleInput(SDL_Event &e)
{
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:  xv -= XVEL; dir=1; break;
      case SDLK_RIGHT: xv += XVEL; dir=0; break;
      case SDLK_SPACE: jump();     break;
    }
  }
  else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
      case SDLK_LEFT:  xv += XVEL; break;
      case SDLK_RIGHT: xv -= XVEL; break;
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

void Player::selectSprite(int wframe)
{
  if (xv == 0) {
    frame = 4-dir;
  } else if (xv < 0 and wframe == FRAME_REFRESH) {
    frame--;
    if(frame < 0 or frame > 3) {
      frame = 2;
    }
  } else if(xv > 0 and wframe == FRAME_REFRESH) {
    frame++;
    if (frame > 7) {
      frame = 5;
    }
  }
  if (onGround > 0) {
    frame = 9-dir;
  }
}

void Player::draw(Window w)
{
  selectSprite(w.frame);
  spritesheet.drawClip(w, sprites[frame], x, y);
}

// relative to camera x,y
void Player::draw(Window w, int cx, int cy)
{
  selectSprite(w.frame);
  spritesheet.drawClip(w, sprites[frame], x-cx, y-cy);
}

