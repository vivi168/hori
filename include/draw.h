#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rect.h"

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 448;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 800;

const int CURSOR_WIDTH = 40;
const int CURSOR_HEIGHT = 40;
const int CURSOR_X_OFFSET = 18;
const int CURSOR_Y_OFFSET = 13;

const std::string TITLE = "hori";

void log_sdl_error(std::string msg);

class Window
{
  private:
  public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    Window();
    bool init();

    void close();
};

class Image
{
  private:
    //SDL_Texture* load_texture(Window w, std::string file);
    SDL_Texture *texture;
  public:
    Image();
    bool init(Window w, std::string path);

    void close();
    void drawClip(Window w, Rect r, int x, int y);
};

class Camera;


