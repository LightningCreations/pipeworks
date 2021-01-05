#ifndef PW_SCENE_HPP
#define PW_SCENE_HPP

namespace pipeworks {

class Scene;

}

#include "gameobject.hpp"

#include <cstdint>
#include <vector>

namespace pipeworks {

class Scene {
  private:
    uint32_t id;
    std::vector<GameObject*> objects;
  public:
    Scene();
    uint32_t get_id();
    void activate();
    void deactivate();
    std::vector<GameObject*> get_objects();
};

}

#endif
