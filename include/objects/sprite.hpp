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
    Sprite(float x, float y, float z, float width, float height, std::vector<ImageData> data);
    Sprite(float x, float y, float z, float width, float height, std::vector<std::string> resources);
    void render(Renderer&);
    void finished_loading();
    bool loaded();
    std::vector<std::string> loadable_resources();
};

}

#endif // PW_OBJECTS_BACKGROUND_HPP
