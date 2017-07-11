#include <iostream>

#include "draw.h"
#include "unit.h"
#include "tilemap.h"
#include "cursor.h"
#include "camera.h"

int main(int argc, char **argv)
{
  Window w;
  Image i;
  Image bg;
  Image t;
  Image c;

  if (w.init() &&
      i.init(w, "mario.png") &&
      bg.init(w, "bg.png") &&
      t.init(w, "tiles.png") &&
      c.init(w, "cursor.png")) {

    TileMap map("map.txt", bg, t);

    Unit p(i);
    Cursor cursor(c);

    Camera camera;

    SDL_Event e;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    bool quit = false;
    while (!quit) {
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
          quit = true;

        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
          if (e.key.keysym.sym == SDLK_ESCAPE)
            quit = true;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
          if (e.button.button == SDL_BUTTON_LEFT) {
            std::cout << cursor.mx(camera) << "\n";
            std::cout << cursor.my(camera) << "\n";
            if ((int)e.button.clicks == 2) {
              std::cout << "hello" << "\n";
            }

            if (p.clicked(cursor.mx(camera), cursor.my(camera))) {
              std::cout << "hitch !" << "\n";
            }

          }
        }

        p.handleInput(e);
      }

      p.update();

      camera.updatePositionFromCursor(cursor);

      //camera.center(p.x, p.y, SPRITEW, SPRITEH);
      camera.keepinbound();

      SDL_RenderClear(w.renderer);

      map.draw(w, camera.x(), camera.y());
      p.draw(w, camera.x(), camera.y());
      cursor.draw(w);

      //std::cout << cursor.x() << ":" << cursor.y() << "\n";
      //std::cout << cursor.mx(camera.x()) << ":" << cursor.my(camera.y()) << "\n";

      SDL_RenderPresent(w.renderer);
    }
  }

  w.close();
  i.close();
  bg.close();
  t.close();
  c.close();

  return 0;

}
