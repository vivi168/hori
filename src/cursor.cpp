#include "cursor.h"

Cursor::Cursor(Image i)
{
  spritesheet = i;
  mouse_x = 0;
  mouse_y = 0;
  cursors[normal] = Rect(0, 0, CURSOR_WIDTH, CURSOR_HEIGHT);
}

void Cursor::getMouseState()
{
  SDL_GetMouseState(&mouse_x, &mouse_y);
}

void Cursor::setSpritesheet(Image i)
{
  spritesheet = i;
}

int Cursor::x()
{
  getMouseState();
  return mouse_x;
}
int Cursor::y()
{
  getMouseState();
  return mouse_y;
}

int Cursor::rx() { return x() - CURSOR_X_OFFSET; }
int Cursor::ry() { return y() - CURSOR_Y_OFFSET; }

int Cursor::mx(Camera c) { return x() + c.x(); }
int Cursor::my(Camera c) { return y() + c.y(); }

void Cursor::draw(Window w)
{
  spritesheet.drawClip(w, cursors[normal], rx(), ry());
}
