#ifndef PW_SCENE_HPP
#define PW_SCENE_HPP

#include <cstdint>

namespace pipeworks {

class Scene {
  private:
    uint32_t id;
  public:
    Scene();
    uint32_t get_id();
};

}

#endif
