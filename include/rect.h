#ifndef RECT_H_
#define RECT_H_

#include <SDL2/SDL.h>

class Rect
{
private:
  SDL_Rect rect;
public:
  Rect();
  Rect(int x, int y, int w, int h);

  int x();
  int y();
  void setx(int i);
  void sety(int i);
  int width();
  int height();
  bool intersects(Rect r);
  SDL_Rect sdlrect();
};

#endif
