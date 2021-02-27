#include <objects/background.hpp>

namespace pipeworks {

Background::Background(float x, float y, float z): GameObject(x, y, z) {}

void Background::render(Renderer &renderer) {
    (void) renderer;
    // I'll implement this properly once I have something for it.
}

} // namespace pipeworks
