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

class Sprite : public GameObject {
  private:
    float x;
    float y;
    // float z; // Since depth sorting doesn't exist yet, neither does a reason for a Z coordinate.
    float width;
    float height;
    std::vector<ImageData> image_data;
    std::vector<std::string> resources;
    bool loaded;
    uint16_t frame; // If someone has more than 65536 animation frames on a single sprite, there is something wrong.
  public:
    Sprite(float x, float y, float z, float width, float height, std::vector<ImageData> data);
    Sprite(float x, float y, float z, float width, float height, std::vector<std::string> resources);
    void render(Renderer&);
    void finished_loading();
    bool is_loaded();
    std::vector<std::string> get_loadable_resources();
};

}

#endif // PW_OBJECTS_BACKGROUND_HPP
