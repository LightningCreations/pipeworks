#ifndef PW_ENGINE_HPP
#define PW_ENGINE_HPP

#include "audiomixer.hpp"
#include "audioplayer.hpp"
#include "event.hpp"
#include "scene.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include "ring_buffer/ring_buffer.h"

#include <atomic>
#include <memory>
#include <stack>
#include <string>
#include <thread>
#include <vector>
#include <optional>
#include <list>

#define PW_VERSION "0.1.0"

namespace pipeworks {

/// \brief The core engine.
///
/// Manages backends as well as loading resources.
class Engine {
  private:
    std::unique_ptr<AudioMixer> m_audio_mixer;
    std::unique_ptr<AudioPlayer> m_audio_player;
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
    std::list<Event> m_events;
    std::optional<InputManager> m_inputMan;
    Soft_Ring_Buffer m_eventQueue;
    void fire_event0(EventType type, void *data);
    void audio_callback(float *data, int len);
    friend void engine_audio_callback_wrap(void *userdata, float *data, int len);
  protected:
    /// \brief Deactivate Scene if it is active *without* notifying it.
    /// \param scene The Scene to deactivate.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// This function is primarily useful for bringing scenes to the front, as notifying the scene of being deactivated is not necessarily useful.
    /// Calling this function without promptly reactivating the Scene could have unintended consequences.
    void deactivate_scene0(Scene &scene);
  public:
    /// \brief Create a new Engine.
    /// \param renderer The Renderer to be used as a backend.
    Engine(std::unique_ptr<Renderer> renderer, std::unique_ptr<AudioPlayer> audio_player, std::unique_ptr<AudioMixer> audio_mixer);

    /// \brief Set the Scene to be used on initialization.
    /// \param scene The Scene to be used as the initial scene.
    /// \pre This may be called before or after the Engine is started. If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    ///
    /// This scene is loaded as if by \ref activate_scene "activate_scene(scene)" when the \ref start() function is called.
    void set_init_scene(std::unique_ptr<Scene> scene);

    /// \brief Set the Scene to be used as a loading transition.
    /// \param scene The Scene to be used when loading.
    /// \pre If the Scene passed to this function needs to load resources, the behavior is undefined.
    /// \pre This may be called before or after the Engine is started. If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    ///
    /// When a Scene is activated, the first thing done is checking if the Scene's resources are all loaded.
    /// If they aren't, the Scene set by this function is activated instead.
    void set_load_scene(std::unique_ptr<Scene> scene);

    /// \brief Start the Engine in a new thread.
    /// \pre Calling this after the Engine has already been started results in undefined behavior.
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
    bool is_running();

    /// \brief Wait for the Engine thread to finish.
    /// \pre Calling this from the Engine thread results in undefined behavior.
    ///
    /// This should not be implemented with a busy loop.
    void join();

    /// \brief Activate a Scene, or move an already active Scene to the front.
    /// \param scene The Scene to activate.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    void activate_scene(Scene &scene);

    /// \brief Deactivate a Scene if a Scene is active.
    /// \param scene The Scene to deactivate.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// In addition to disabling rendering and updating, this function also notifies the Scene it has been deactivated so cleanup calls may be made.
    void deactivate_scene(Scene &scene);

    /// \brief Register an Event.
    /// \param event The Event to register.
    /// \pre This may be called before or after the Engine is started. If the Engine is started, this function must be called from the Engine thread; otherwise, the behavior is undefined.
    void register_event(std::unique_ptr<Event> event);

    /// \brief Fire an Event.
    /// \param type The category of events to fire.
    /// \param data The event-specific data corresponding to the event fired.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// Specifically, this runs the callback on any and all \ref Event "Events" that have been previously registered with \ref register_event "register_event" corresponding to the type specified.
    void fire_event(EventType type, void *data);

    /// \brief Get the active Renderer.
    /// \return The in-use render backend implementation.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// The Renderer contains the interfaces to drawing and getting input (currently), making it essential for most functions that access the Engine.
    Renderer& renderer();

    /// \brief Gets the Input Manager
    /// \pre This must be called either before the Engine is started, or on the Engine Thread.
    ///
    /// The Input Manager allows for synchronous handling of Key Inputs
    InputManager& input_manager();

    void set_bgm(const AudioData *data);
    void add_sfx(const AudioData *data);
    void play_sfx(const AudioData *data);
};

}

#endif // PW_ENGINE_HPP
