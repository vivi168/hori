#pragma once

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
    bool includes(int, int);
    SDL_Rect sdlrect();
};
