#ifndef RECT_H_
#define RECT_H_

class Point
{
private:
public:
  int x,y;

  Point();
  Point(int i, int j);
};

class Rect
{
private:
public:
  Point tl,br;

  Rect();
  Rect(int x, int y, int w, int h);

  int width() const;
  int height() const;
  bool intersects(Rect r);
};

#endif
