#include <objects/sprite.hpp>
#include <resourcemanager.hpp>

namespace pipeworks {

Sprite::Sprite(float x, float y, float z, float width, float height, std::vector<ImageData> data):
    x(x), y(y), width(width), height(height), image_data(data), loaded(true) {
    (void) z; // Unused until we have depth sorting
}

Sprite::Sprite(float x, float y, float z, float width, float height, std::vector<std::string> resources):
    x(x), y(y), width(width), height(height), resources(resources), loaded(false) {
    (void) z;
}

void Sprite::render(Renderer &renderer) {
    if(!loaded) return; // Can't render if we aren't loaded
    (void) x;
    (void) y;
    (void) width;
    (void) height;
    (void) image_data;
}

void Sprite::finished_loading() {
    for(std::string resource : resources) {
        image_data.push_back(g_resourcemanager.get_imagedata(resource));
    }
}

bool Sprite::is_loaded() {
    return loaded;
}

std::vector<std::string> Sprite::get_loadable_resources() {
    return resources;
}

} // namespace pipeworks
