#include <cassert>
#include <objects/sprite.hpp>
#include <resourcemanager.hpp>

namespace pipeworks {

Sprite::Sprite(float x, float y, float z, float width, float height, std::vector<ImageData> data):
    GameObject(x, y, z), m_width(width), m_height(height), m_image_data(data), m_loaded(true), m_frame(0) {}

Sprite::Sprite(float x, float y, float z, float width, float height, std::vector<std::string> resources):
    GameObject(x, y, z), m_width(width), m_height(height), m_resources(resources), m_loaded(false), m_frame(0) {}

uint16_t Sprite::frame() {
    return m_frame;
}

void Sprite::set_frame(uint16_t frame) {
    m_frame = frame;
}

void Sprite::render(Renderer &renderer) {
    if(!m_loaded) return; // Can't render if we aren't loaded
    assert(m_frame >= 0 && m_frame < m_image_data.size());
    ImageData image = m_image_data[m_frame];
    const uint32_t iw = image.width();
    const uint32_t ih = image.height();
    const uint8_t *id = image.data();
    float pw = m_width/iw, ph = m_height/ih; // Width/height of one image pixel
    // TODO: Optimize for images substantially larger than size on screen
    // TODO: Prevent floating point imprecision aliasing (if possible to do without slowdown)
    for(uint32_t ix = 0; ix < iw; ix++) {
        for(uint32_t iy = 0; iy < ih; iy++) {
            renderer.fill_rect(x() + pw*ix, y() - ph*iy, pw, ph,
                id[(ix+iy*iw)*4],
                id[(ix+iy*iw)*4+1],
                id[(ix+iy*iw)*4+2],
                id[(ix+iy*iw)*4+3]);
        }
    }
}

void Sprite::finished_loading() {
    for(std::string resource : m_resources) {
        m_image_data.push_back(g_resourcemanager.image_data(resource));
    }
    m_loaded = true;
}

bool Sprite::is_loaded() {
    return m_loaded;
}

std::vector<std::string> Sprite::loadable_resources() {
    return m_resources;
}

} // namespace pipeworks
