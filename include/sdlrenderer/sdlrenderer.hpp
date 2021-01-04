#ifndef PW_SDLRENDERER_HPP
#define PW_SDLRENDERER_HPP

#include "../renderer.hpp"

#include <SDL.h>

namespace pipeworks {

class SDLRenderer : public Renderer {
  private:
    SDL_Window *m_window;
    bool m_is_close_requested;
    uint32_t next_time;
    std::vector<Scene> active_scenes;
  public:
    SDLRenderer();
    ~SDLRenderer();
    void open_window();
    void close_window();
    bool is_close_requested();
    void render_poll();
    void sync(uint32_t);
    void set_active_scene_list(std::vector<Scene>);
};

}

#endif // PW_SDLRENDERER_HPP
