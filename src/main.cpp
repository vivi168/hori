#include <iostream>

#include "draw.h"
#include "player.h"

int main()
{
  Window w;
  Image i;
  Image bg;

  if (w.init() && i.init(w, "mario_a.png") && bg.init(w, "bg.png")) {
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    Player p(i);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
      //Event Polling
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
        p.handleInput(e);
      }

      p.move();

      //Center the camera over the dot
      camera.x = (p.x + SPRITEW / 2) - SCREEN_WIDTH / 2;
      camera.y = (p.y + SPRITEH / 2) - SCREEN_HEIGHT / 2;

      //Keep the camera in bounds
      if (camera.x < 0) {
        camera.x = 0;
      }
      if (camera.y < 0) {
        camera.y = 0;
      }
      if (camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
      }
      if (camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
      }

      SDL_RenderClear(w.renderer);
      bg.drawClip(w, Rect(0,0,1296,794), 0-camera.x, 0-camera.y);
      p.draw(w, camera.x, camera.y);
      SDL_RenderPresent(w.renderer);

      w.nextFrame();
    }
  }

  w.close();
  i.close();

  return 0;

}
