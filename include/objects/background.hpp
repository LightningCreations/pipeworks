#ifndef PW_OBJECTS_BACKGROUND_HPP
#define PW_OBJECTS_BACKGROUND_HPP

namespace pipeworks {

class Background;

}

#include "../gameobject.hpp"

namespace pipeworks {

/// \brief A background layer.
///
/// This is a very incomplete class; as such, expect the API to be incredibly unstable.
class Background : public GameObject {
  private:
    float m_x;
    float m_y;
    // float m_z; // Since depth sorting doesn't exist yet, neither does a reason for a Z coordinate.
  public:
    /// \brief Create a new Background.
    /// \param x The horizontal position of the Background
    /// \param y The vertical position of the Background
    /// \param z The depth of the Background (unused)
    Background(float x, float y, float z);
    void render(Renderer &renderer);
};

}

#endif // PW_OBJECTS_BACKGROUND_HPP
