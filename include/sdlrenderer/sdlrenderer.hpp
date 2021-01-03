#ifndef PW_SDLRENDERER_HPP
#define PW_SDLRENDERER_HPP

#include "../renderer.hpp"

#include <SDL.h>

namespace pipeworks {

class SDLRenderer : public Renderer {
  private:
    SDL_Window *window;
  public:
    SDLRenderer();
    ~SDLRenderer();
    void open_window();
    void close_window();
    bool is_close_requested();
};

}

#endif // PW_SDLRENDERER_HPP
