#ifndef PW_SDLRENDERER_HPP
#define PW_SDLRENDERER_HPP

#include "../renderer.hpp"

#include <SDL.h>
#include <memory>

namespace pipeworks {

/// \brief Renderer implementation using SDL2.
class SDLRenderer : public Renderer {
  private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    SDL_Texture *m_texture = nullptr;
    uint8_t *m_pixels = nullptr;
    bool m_close_requested = false;
    uint32_t m_next_time = 0;
    std::vector<Scene> *m_active_scenes;
    uint32_t m_width;
    uint32_t m_height;
    float m_xoa;
    bool m_keys_down[256];
    Engine *m_engine;
  public:
    SDLRenderer();
    ~SDLRenderer();
    void set_active_engine(Engine*) override;
    void set_active_scene_list(std::vector<Scene>*) override;
    void set_width(uint32_t) override;
    void set_height(uint32_t) override;
    void open_window() override;
    void close_window() override;
    bool is_close_requested() override;
    void render_poll() override;
    void sync(uint32_t) override;
    void fill_rect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) override;
    void clear() override;
    uint32_t width() override;
    uint32_t height() override;
    bool is_key_down(char c) override;
};

}

#endif // PW_SDLRENDERER_HPP
