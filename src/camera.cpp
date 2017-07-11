#include "camera.h"

Camera::Camera()
{
  camera = Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

int Camera::x() { return camera.x(); }
int Camera::y() { return camera.y(); }

void Camera::center(int x, int y, int w, int h)
{
  camera.setx((x + w / 2) - SCREEN_WIDTH / 2);
  camera.sety((y + h / 2) - SCREEN_HEIGHT / 2);
}

void Camera::move(Direction dir)
{
  switch (dir) {
    case up:
      camera.sety(camera.y() - 10);
      break;
    case down:
      camera.sety(camera.y() + 10);
      break;
    case left:
      camera.setx(camera.x() - 10);
      break;
    case right:
      camera.setx(camera.x() + 10);
      break;
  }
}

void Camera::keepinbound()
{
  if (camera.x() < 0)
    camera.setx(0);
  if (camera.y() < 0)
    camera.sety(0);

  if (camera.x() > LEVEL_WIDTH - camera.width())
    camera.setx(LEVEL_WIDTH - camera.width());
  if (camera.y() > LEVEL_HEIGHT - camera.height())
    camera.sety(LEVEL_HEIGHT - camera.height());

}

bool Camera::intersects(Rect r)
{
  return camera.intersects(r);
}

void Camera::updatePositionFromCursor(Cursor cursor)
{
  if (cursor.x() == 0) {
    move(Camera::left);
  }
  if (cursor.x() == SCREEN_WIDTH - 1) {
    move(Camera::right);
  }
  if (cursor.y() == 0) {
    move(Camera::up);
  }
  if (cursor.y() == SCREEN_HEIGHT - 1) {
    move(Camera::down);
  }
}
