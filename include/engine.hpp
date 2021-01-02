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
    std::unique_ptr<Scene> init_scene;
    bool running; // FIXME: Needs thread safety
  public:
    Engine(std::unique_ptr<Renderer> renderer);
    void activate_scene(Scene &scene);
    void deactivate_scene(Scene &scene);
    void set_init_scene(std::unique_ptr<Scene> scene);
    void start();
    void stop();
};

}

#endif // PW_ENGINE_HPP
