#ifndef PW_GAMEOBJECT_HPP
#define PW_GAMEOBJECT_HPP

namespace pipeworks {

class GameObject;

}

#include "renderer.hpp"

namespace pipeworks {

class GameObject {
  public:
    virtual ~GameObject() = 0;
    virtual void render(const Renderer &renderer) = 0;
};

}

#endif // PW_GAMEOBJECT_HPP
