#ifndef PW_ENGINE_HPP
#define PW_ENGINE_HPP

namespace pipeworks {

class Engine;

}

#include "scene.hpp"
#include "renderer.hpp"

#include <atomic>
#include <memory>
#include <stack>
#include <string>
#include <thread>
#include <vector>

#define PW_VERSION "0.1.0"

namespace pipeworks {

class Engine {
  private:
    std::unique_ptr<Renderer> m_renderer;
    std::vector<Scene> m_active_scenes;
    std::unique_ptr<Scene> m_init_scene;
    std::unique_ptr<Scene> m_load_scene;
    Scene *m_pending_scene;
    std::stack<std::string> m_load_tasks;
    std::thread m_engine_thread;
    std::atomic_bool m_running;
    void start0(); // Start in new thread
    std::atomic_uint8_t m_active_load_threads;
    void load_resource(std::string resource);
  protected:
    void deactivate_scene0(Scene &scene); // Deactivate scene without notification; useful in reactivation
  public:
    Engine(std::unique_ptr<Renderer> renderer);
    void set_init_scene(std::unique_ptr<Scene> scene);
    void set_load_scene(std::unique_ptr<Scene> scene);
    void start();
    void stop();
    bool running();
    void join(); // Wait for engine thread to finish
    void activate_scene(Scene &scene);
    void deactivate_scene(Scene &scene);
};

}

#endif // PW_ENGINE_HPP
