#ifndef PW_GAMEOBJECT_HPP
#define PW_GAMEOBJECT_HPP

namespace pipeworks {

class GameObject;

}

#include <string>
#include <vector>

#include "renderer.hpp"

namespace pipeworks {

class GameObject {
  public:
    virtual ~GameObject() = 0;
    virtual void render(Renderer &renderer) = 0; // Called from engine thread.
    virtual void finished_loading() {} // Called from engine thread when all resources from this object are loaded. By default, does nothing.
    virtual bool is_loaded() { return true; } // Called from engine thread to detect if resources need to be loaded before the object can be used.
    virtual std::vector<std::string> get_loadable_resources() { return std::vector<std::string>(); } // Called from engine thread to determine what resources need to be loaded.
};

}

#endif // PW_GAMEOBJECT_HPP
