#ifndef PW_OBJECTS_BACKGROUND_HPP
#define PW_OBJECTS_BACKGROUND_HPP

namespace pipeworks {

class Background;

}

#include "../gameobject.hpp"

namespace pipeworks {

class Background : public GameObject {
  private:
    float x;
    float y;
    // float z; // Since depth sorting doesn't exist yet, neither does a reason for a Z coordinate.
  public:
    Background(float x, float y, float z);
    void render(Renderer&);
};

}

#endif // PW_OBJECTS_BACKGROUND_HPP
