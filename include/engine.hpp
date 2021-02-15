#ifndef PW_ENGINE_HPP
#define PW_ENGINE_HPP

/// \brief Root namespace
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

/// \brief The core engine.
///
/// Manages backends as well as loading resources.
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
    /// \brief Deactivate Scene if it is active *without* notifying it.
    /// \param scene The Scene to deactivate.
    ///
    /// This function is primarily useful for bringing scenes to the front, as notifying the scene of being deactivated is not necessarily useful.
    /// Calling this function without promptly reactivating the Scene could have unintended consequences.
    ///
    /// Calling this from any thread except the Engine thread results in undefined behavior.
    void deactivate_scene0(Scene &scene);
  public:
    /// \brief Create a new Engine.
    /// \param renderer The Renderer to be used as a backend.
    Engine(std::unique_ptr<Renderer> renderer);
    /// \brief Set the Scene to be used on initialization.
    /// \param scene The Scene to be used as the initial scene.
    ///
    /// This scene is loaded as if by \ref activate_scene "activate_scene(scene)" when the \ref start() function is called.
    /// This may be called before or after the Engine is started.
    /// If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    void set_init_scene(std::unique_ptr<Scene> scene);
    /// \brief Set the Scene to be used as a loading transition.
    /// \param scene The Scene to be used when loading.
    ///
    /// When a Scene is activated, the first thing done is checking if the Scene's resources are all loaded.
    /// If they aren't, the Scene set by this function is activated instead.
    /// If the Scene passed to this function needs to load resources, the behavior is undefined.
    ///
    /// This may be called before or after the Engine is started.
    /// If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    void set_load_scene(std::unique_ptr<Scene> scene);
    /// \brief Start the Engine in a new thread.
    ///
    /// Calling this after the Engine has already been started results in undefined behavior.
    void start();
    /// \brief Stop the Engine.
    ///
    /// This may be called from any thread. It will cause the Engine to shutdown at the end of the current cycle.
    void stop();
    /// \brief Determine if the Engine is still running.
    /// \return `true` if the Engine is running, `false` if it isn't.
    ///
    /// This function is most useful to determine if the Engine has stopped midframe.
    /// For waiting in the main thread, \ref join() should be used instead.
    ///
    /// This may be called from any thread.
    bool running();
    /// \brief Wait for the Engine thread to finish.
    ///
    /// This should not be implemented with a busy loop.
    ///
    /// Calling this from the Engine thread results in undefined behavior.
    void join();
    /// \brief Activate a Scene, or move an already active Scene to the front.
    /// \param scene The Scene to activate.
    ///
    /// Calling this from any thread except the Engine thread results in undefined behavior.
    void activate_scene(Scene &scene);
    /// \brief Deactivate a Scene if a Scene is active.
    /// \param scene The Scene to deactivate.
    ///
    /// In addition to disabling rendering and updating, this function also notifies the Scene it has been deactivated so cleanup calls may be made.
    ///
    /// Calling this from any thread except the Engine thread results in undefined behavior.
    void deactivate_scene(Scene &scene);
};

}

#endif // PW_ENGINE_HPP
