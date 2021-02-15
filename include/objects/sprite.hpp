#ifndef PW_OBJECTS_SPRITE_HPP
#define PW_OBJECTS_SPRITE_HPP

namespace pipeworks {

class Sprite;

}

#include <memory>
#include <string>
#include <vector>

#include "../gameobject.hpp"
#include "../imagedata.hpp"

namespace pipeworks {

/// \brief A movable, resizable object.
class Sprite : public GameObject {
  private:
    float m_x;
    float m_y;
    // float m_z; // Since depth sorting doesn't exist yet, neither does a reason for a Z coordinate.
    float m_width;
    float m_height;
    std::vector<ImageData> m_image_data;
    std::vector<std::string> m_resources;
    bool m_loaded;
    uint16_t m_frame; // If someone has more than 65536 animation frames on a single sprite, there is something wrong.
  public:
    /// \brief Create a Sprite with position, size, and existing image data.
    /// \param x The horizontal position of the Sprite.
    /// \param y The vertical position of the Sprite.
    /// \param z The depth of the Sprite. (unused)
    /// \param width The width of the Sprite, where the screen is 2 units high.
    /// \param height The height of the Sprite, where the screen is 2 units high.
    /// \param data A list of ImageData objects for each frame of animation.
    Sprite(float x, float y, float z, float width, float height, std::vector<ImageData> data);
    /// \brief Create a Sprite with position, size, and files to load image data from.
    /// \param x The horizontal position of the Sprite.
    /// \param y The vertical position of the Sprite.
    /// \param z The depth of the Sprite. (unused)
    /// \param width The width of the Sprite, where the screen is 2 units high.
    /// \param height The height of the Sprite, where the screen is 2 units high.
    /// \param resources A list of paths to resources containing image data for each frame of animation.
    Sprite(float x, float y, float z, float width, float height, std::vector<std::string> resources);
    void render(Renderer&);
    void finished_loading();
    bool loaded();
    std::vector<std::string> loadable_resources();
    /// \brief Set the current animation frame.
    /// \param frame The animation frame to start rendering.
    /// \pre This may be called before or after the Engine is started. If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    void set_frame(uint16_t frame);
    /// \brief Get the current animation frame.
    /// \param frame The animation frame currently being drawn.
    /// \pre This may be called before or after the Engine is started. If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    uint16_t frame();
};

}

#endif // PW_OBJECTS_BACKGROUND_HPP
