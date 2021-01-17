#include <objects/background.hpp>

namespace pipeworks {

Background::Background(float x, float y, float z): x(x), y(y) {
    (void) z;
}

void Background::render(Renderer &renderer) {
    (void) x;
    (void) y;
    // I'll implement this properly once I have something for it.
}

} // namespace pipeworks
