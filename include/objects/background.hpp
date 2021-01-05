#ifndef PW_OBJECTS_BACKGROUND_HPP
#define PW_OBJECTS_BACKGROUND_HPP

namespace pipeworks {

class Background;

}

#include "../gameobject.hpp"

namespace pipeworks {

class Background : public GameObject {
  public:
    Background(float x, float y, float z);
    void render(Renderer&);
}

}

#endif PW_OBJECTS_BACKGROUND_HPP
