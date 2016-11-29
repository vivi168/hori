#include <iostream>

#include "draw.h"
#include "player.h"

int main(int argc, char **argv)
{
  Window w;
  Image i;
  Image bg;

  if (w.init() && i.init(w, "mario_a.png") && bg.init(w, "bg.png")) {
    Camera camera;

    Player p(i);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
        p.handleInput(e);
      }

      p.update();

      camera.center(p.x, p.y, SPRITEW, SPRITEH);
      camera.keepinbound();

      SDL_RenderClear(w.renderer);
      bg.drawClip(w, Rect(0,0,1296,794), 0-camera.x(), 0-camera.y());
      p.draw(w, camera.x(), camera.y());
      SDL_RenderPresent(w.renderer);
    }
  }

  w.close();
  i.close();

  return 0;

}
