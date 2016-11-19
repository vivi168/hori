#include "rect.h"

Point::Point()
{
  x = 0; y = 0;
}

Point::Point(int i, int j)
{
  x = i; y = j;
}

Rect::Rect()
{
}

Rect::Rect(int x, int y, int w, int h)
{
  tl = Point(x,y);
  br = Point(x+w, y+h);
}

int Rect::width() const
{
  return br.x - tl.x;
}

int Rect::height() const
{
  return br.y - tl.y;
}

bool Rect::intersects(Rect r)
{
  return (tl.x < r.br.x && br.x > r.tl.x &&
          tl.y < r.br.y && br.y > r.tl.y);
}
