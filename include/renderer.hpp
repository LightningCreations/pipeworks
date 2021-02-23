#ifndef PW_RENDERER_HPP
#define PW_RENDERER_HPP

namespace pipeworks {

class Renderer;

}

#include "scene.hpp"

#include <cstdint>
#include <vector>

namespace pipeworks {

/// \brief A render backend
class Renderer {
  public:
    virtual ~Renderer() = 0;
    /// \brief Set the list of active Scenes.
    /// \pre This is expected to be run from the Engine on initialization, running any other time is undefined behavior.
    ///
    /// The active Scene list is edited by the Engine, but the Renderer is allowed to edit and rearrange GameObjects within each Scene.
    virtual void set_active_scene_list(std::vector<Scene>*) = 0;
    /// \brief Set the width of the render area in pixels.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    virtual void set_width(uint32_t width) = 0;
    /// \brief Set the height of the render area in pixels.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    virtual void set_height(uint32_t height) = 0;
    /// \brief Open a window, or otherwise start displaying a render target.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    virtual void open_window() = 0;
    /// \brief Open a window, or otherwise stop displaying the render target.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    /// \pre Running this without having opened a window causes undefined behavior.
    virtual void close_window() = 0;
    /// \brief Determine if the user or OS has requested the window (or other render target) to close.
    /// \return `true` if the window (or other render target) was requested to be closed, `false` otherwise.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    virtual bool is_close_requested() = 0;
    /// \brief Render, then get input for the next frame.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    ///
    /// The reason input is taken after rendering is to reduce input lag.
    /// If input was taken first, the input from the previous frame would still be getting used.
    /// As a result, there would be consistently over a frame of input lag.
    ///
    /// It would be possible to split this into two functions, but there isn't an actual benefit.
    /// In addition, breaking into two functions creates more delay due to multiple virtual calls.
    virtual void render_poll() = 0;
    /// \brief Synchronize to a specific frame rate.
    /// \param fps The FPS value to synchronize to.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    ///
    /// This function can be implemented by any method. VSync is possible but not necessary.
    virtual void sync(uint32_t fps) = 0;
    /// \brief Fill a rectangle with a specific color.
    /// \param x The horizonal position of the top-left corner of the rectangle, where the screen is 2 units tall and the center is (0, 0).
    /// \param y The vertical position of the top-left corner of the rectangle, where the screen is 2 units tall and the center is (0, 0).
    /// \param w The width of the rectangle, where the screen is 2 units tall.
    /// \param h The height of the rectangle, where the screen is 2 units tall.
    /// \param r The red color of the rectangle in the range of [0,256).
    /// \param g The green color of the rectangle in the range of [0,256).
    /// \param b The blue color of the rectangle in the range of [0,256).
    /// \param a The transparancy value of the rectangle in the range of [0,256), where 0 is fully transparent and 255 is fully opaque.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    ///
    /// This is the basic unit of any drawing calls. Any more advanced drawing functions can always be implemented by multiple invocations of this.
    ///
    /// Currently, alpha is implemented by making the pixel either fully opaque or fully transparent. This will be changed later.
    virtual void fill_rect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
    /// \brief Get the width of the screen.
    /// \return The width of the screen in pixels.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    virtual uint32_t width() = 0;
    /// \brief Get the height of the screen.
    /// \return The height of the screen in pixels.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    virtual uint32_t height() = 0;
    /// \brief Determine if a specific character is pressed.
    /// \return `true` if the key is down, `false` otherwise.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    ///
    /// This API is preemptively deprecated in favor of an upcoming API.
    virtual bool is_key_down(char c) = 0;
    /// \brief Determine if a specific (wide) character is pressed.
    /// \return `true` if the key is down, `false` otherwise.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    ///
    /// This API is preemptively deprecated in favor of an upcoming API.
    virtual bool is_key_down(wchar_t c) { // If the underlying implementation doesn't support wide characters, we'll do it for them
        if(c > 0xff) return 0;
        return is_key_down(c);
    }
};

}

#endif
