#pragma once

#include "rect.h"
#include "cursor.h"

class Cursor;

class Camera
{
  private:
    Rect camera;
  public:
    enum Direction {
      up, down, left, right
    };
    int x();
    int y();

    Camera();
    void center(int, int, int, int);
    void move(Direction);
    void keepinbound();
    bool intersects(Rect);
    void updatePositionFromCursor(Cursor);
};
