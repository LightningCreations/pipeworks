#include <objects/background.hpp>

namespace pipeworks {

Background::Background(float x, float y, float z): m_x(x), m_y(y) {
    (void) z;
}

void Background::render(Renderer &renderer) {
    (void) m_x;
    (void) m_y;
    (void) renderer;
    // I'll implement this properly once I have something for it.
}

} // namespace pipeworks
