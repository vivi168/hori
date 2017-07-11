#pragma once
#include <map>
#include "draw.h"
#include "camera.h"

class Cursor
{
  private:
    enum State {
      normal, hover
    };

    int mouse_x, mouse_y;
    Image spritesheet;
    std::map<State, Rect> cursors;

  public:
    Cursor(Image);

    void getMouseState();
    void setSpritesheet(Image);
    int x();
    int y();
    int rx(); // with offset to center
    int ry(); // with offset to center
    int mx(Camera); // relative to map
    int my(Camera); // relative to map
    void draw(Window);

};
