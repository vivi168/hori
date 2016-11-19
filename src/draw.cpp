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

void Image::drawClip(SDL_Renderer *renderer, Rect r, int x, int y)
{
  SDL_Rect clip;
  SDL_Rect dest;

  clip = {r.tl.x, r.tl.y, r.width(), r.height()};
  dest  = {x, y, r.width(), r.height()};

  SDL_RenderCopy(renderer, texture, &clip, &dest);

}
