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
    uint32_t m_id;
    std::vector<GameObject*> m_objects;
  public:
    Scene();
    uint32_t id();
    void activate();
    void deactivate();
    std::vector<GameObject*> objects();
    void add_object(GameObject*);
    bool loaded(); // Checks every object
};

}

#endif
