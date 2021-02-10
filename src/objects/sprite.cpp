#include <cassert>
#include <objects/sprite.hpp>
#include <resourcemanager.hpp>

namespace pipeworks {

Sprite::Sprite(float x, float y, float z, float width, float height, std::vector<ImageData> data):
    x(x), y(y), width(width), height(height), image_data(data), loaded(true), frame(0) {
    (void) z; // Unused until we have depth sorting
}

Sprite::Sprite(float x, float y, float z, float width, float height, std::vector<std::string> resources):
    x(x), y(y), width(width), height(height), resources(resources), loaded(false), frame(0) {
    (void) z;
}

void Sprite::render(Renderer &renderer) {
    if(!loaded) return; // Can't render if we aren't loaded
    assert(frame >= 0 && frame < image_data.size());
    ImageData image = image_data[frame];
    const uint32_t iw = image.width();
    const uint32_t ih = image.height();
    const uint8_t *id = image.data();
    float pw = width/iw, ph = height/ih; // Width/height of one image pixel
    // TODO: Optimize for images substantially larger than size on screen
    // TODO: Prevent floating point imprecision aliasing (if possible to do without slowdown)
    for(uint32_t ix = 0; ix < iw; ix++) {
        for(uint32_t iy = 0; iy < ih; iy++) {
            renderer.fill_rect(x + pw*ix, y + ph*iy, pw, ph,
                id[(ix+iy*iw)*4],
                id[(ix+iy*iw)*4+1],
                id[(ix+iy*iw)*4+2],
                id[(ix+iy*iw)*4+3]);
        }
    }
}

void Sprite::finished_loading() {
    for(std::string resource : resources) {
        image_data.push_back(g_resourcemanager.get_image_data(resource));
    }
    loaded = true;
}

bool Sprite::is_loaded() {
    return loaded;
}

std::vector<std::string> Sprite::get_loadable_resources() {
    return resources;
}

} // namespace pipeworks
