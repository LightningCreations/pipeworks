#ifndef PW_RENDERER_HPP
#define PW_RENDERER_HPP

namespace pipeworks {

class Renderer;

}

#include "scene.hpp"

#include <cstdint>
#include <vector>

namespace pipeworks {

class Renderer {
  public:
    virtual ~Renderer() = 0;
    virtual void set_active_scene_list(std::vector<Scene>*) = 0;
    virtual void set_width(uint32_t) = 0;
    virtual void set_height(uint32_t) = 0;
    virtual void open_window() = 0;
    virtual void close_window() = 0;
    virtual bool is_close_requested() = 0;
    virtual void render_poll() = 0; // Render, then poll for next frame
    virtual void sync(uint32_t) = 0; // Sync to FPS
    virtual void fill_rect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0; // Called from GameObject, replacement for plot_pixel
    virtual uint32_t get_width() = 0; // Called from GameObject
    virtual uint32_t get_height() = 0; // Called from GameObject
    virtual bool key_down(char c) = 0;
    virtual bool key_down(wchar_t c) { // If the underlying implementation doesn't support wide characters, we'll do it for them
        if(c > 0xff) return 0;
        return key_down(c);
    }
};

}

#endif
