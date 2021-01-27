#ifndef PW_ENGINE_HPP
#define PW_ENGINE_HPP

namespace pipeworks {

class Engine;

}

#include "scene.hpp"
#include "renderer.hpp"

#include <memory>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#define PW_VERSION "0.1.0"

namespace pipeworks {

class Engine {
  private:
    std::unique_ptr<Renderer> renderer;
    std::vector<Scene> active_scenes;
    std::unique_ptr<Scene> init_scene;
    std::unique_ptr<Scene> load_scene;
    Scene *pending_scene;
    std::stack<std::string> load_tasks;
    std::thread engine_thread;
    bool running; // FIXME: Needs thread safety
    void start0(); // Start in new thread
  protected:
    void deactivate_scene0(Scene &scene); // Deactivate scene without notification; useful in reactivation
  public:
    Engine(std::unique_ptr<Renderer> renderer);
    void set_init_scene(std::unique_ptr<Scene> scene);
    void set_load_scene(std::unique_ptr<Scene> scene);
    void start();
    void stop();
    bool is_running();
    void join(); // Wait for thread to finish
    void activate_scene(Scene &scene);
    void deactivate_scene(Scene &scene);
};

}

#endif // PW_ENGINE_HPP
