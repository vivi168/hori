#include <iostream>
#include "rect.h"

Rect::Rect()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;
}

Rect::Rect(int x, int y, int w, int h)
{
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}

int Rect::x() { return rect.x; }

int Rect::y() { return rect.y; }

void Rect::setx(int i) { rect.x = i; }
void Rect::sety(int i) { rect.y = i; }

int Rect::width() { return rect.w; }

int Rect::height() { return rect.h; }

bool Rect::intersects(Rect r)
{
  // return (tl.x < r.br.x && br.x > r.tl.x &&
  //         tl.y < r.br.y && br.y > r.tl.y);
  return (x() < (r.x() + r.width()) && (x() + width()) > r.x() &&
      y() < (r.y() + r.height()) && (y() + height()) > r.y());
}

bool Rect::includes(int a, int b)
{
  return a > x() && a < (x() + width()) &&
    b > y() && b < y() + height();
}

SDL_Rect Rect::sdlrect()
{
  return rect;
}
