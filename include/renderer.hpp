#ifndef PW_RENDERER_HPP
#define PW_RENDERER_HPP

#include <cstdint>

namespace pipeworks {

class Renderer {
  public:
    virtual ~Renderer() = 0;
    virtual void open_window() = 0;
    virtual void close_window() = 0;
    virtual bool is_close_requested() = 0;
    virtual void render_poll() = 0; // Render, then poll for next frame
    virtual void sync(uint32_t) = 0; // Sync to FPS
};

}

#endif
