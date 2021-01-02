#ifndef PW_ENGINE_HPP
#define PW_ENGINE_HPP

#include <memory>
#include <vector>
#include "scene.hpp"
#include "renderer.hpp"

namespace pipeworks {

class Engine {
  private:
    std::unique_ptr<Renderer> renderer;
    std::vector<Scene> active_scenes;
  public:
    Engine(std::unique_ptr<Renderer> renderer);
    void activate_scene(Scene &scene);
    void deactivate_scene(Scene &scene);
};

}

#endif // PW_ENGINE_HPP
