#include <iostream>

#include "draw.h"

void log_sdl_error(std::string msg) {
  std::cout << msg << " : " << SDL_GetError() << "\n";
}

Window::Window()
{
  window = NULL;
  renderer = NULL;
}

bool Window::init()
{
  bool success = true;

  window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (window == NULL){
    log_sdl_error("CreateWindow");
    success = false;
  }

  renderer = SDL_CreateRenderer(window, -1,
                                SDL_RENDERER_ACCELERATED |
                                SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL){
    log_sdl_error("CreateRenderer");
    success = false;
  }

  return success;
}

void Window::close()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

Image::Image()
{
  texture = NULL;
}

bool Image::init(Window w, std::string path)
{
  bool success = true;
  texture = IMG_LoadTexture(w.renderer, path.c_str());

  if (texture == NULL) {
    log_sdl_error("CreateImage");
    success = false;
  }

  return success;
}

void Image::close()
{
  SDL_DestroyTexture(texture);
  IMG_Quit();
}

void Image::drawClip(Window w, Rect r, int x, int y)
{
  SDL_Rect clip;
  SDL_Rect dest;

  clip = r.sdlrect();
  dest  = {x, y, r.width(), r.height()};

  SDL_RenderCopy(w.renderer, texture, &clip, &dest);
}

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

void Camera::keepinbound()
{
  if (camera.x() < 0) {
    camera.setx(0);
  }
  if (camera.y() < 0) {
    camera.sety(0);
  }
  if (camera.x() > LEVEL_WIDTH - camera.width()) {
    camera.setx(LEVEL_WIDTH - camera.width());
  }
  if (camera.y() > LEVEL_HEIGHT - camera.height()) {
    camera.sety(LEVEL_HEIGHT - camera.height());
  }

}

bool Camera::intersects(Rect r) {
  return camera.intersects(r);
}
