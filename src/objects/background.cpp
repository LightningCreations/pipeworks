#include <objects/background.hpp>

namespace pipeworks {

Background::Background(float x, float y, float z): x(x), y(y) {}

void Background::render(Renderer &renderer) {
    renderer.fill_rect(x, y, 1, 1, 127, 195, 255, 255); // Horrible background, for sake of example
}

} // namespace pipeworks
