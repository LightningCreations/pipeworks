#ifndef PW_SCENE_HPP
#define PW_SCENE_HPP

namespace pipeworks {

class Scene;

}

#include "gameobject.hpp"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace pipeworks {

/// \brief Group of \ref GameObject "GameObjects", to be switched out for different gameplay moments.
class Scene {
  private:
    uint32_t m_id;
    std::unordered_map<std::string, GameObject*> m_named_objects;
    std::vector<GameObject*> m_objects;
    float m_camera_x;
    float m_camera_y;
  public:
    /// \brief Creates a Scene.
    Scene();
    /// \brief Gets the ID of the Scene
    /// \return The unique ID of the Scene (generated at initialization)
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    uint32_t id() const;
    /// \brief Notifies the Scene that it is on screen.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void activate();
    /// \brief Notifies the Scene that it is no longer on screen.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void deactivate();
    /// \brief Get a list of \ref GameObject "GameObjects" in the Scene.
    /// \return List of every GameObject currently in the Scene. The objects can be modified, but modifying the list doesn't change the internal structure.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    std::vector<GameObject*> objects() const;
    /// \brief Add a GameObject to the Scene.
    /// \param obj GameObject to be added to the Scene.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void add_object(GameObject *obj);
    /// \brief Add a GameObject to the Scene, with an identifier for accessing later.
    /// \param obj GameObject to be added to the Scene.
    /// \param id Unique identifier of the object.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void add_object(GameObject *obj, std::string id);
    /// \brief Get an object from the Scene that has previously been tagged with an identifier.
    /// \param id Unique identifier of the object.
    /// \return The object represented by id.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    GameObject &get_object(std::string id);
    /// \brief Determine if the Scene is loaded.
    /// \return `true` if every GameObject in the Scene is loaded, `false` otherwise.
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    bool is_loaded() const; // Checks every object
    /// \brief Set the X translation of objects in the scene
    /// \param x The new X translation
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void set_camera_x(float x);
    /// \brief Set the Y translation of objects in the scene
    /// \param y The new Y translation
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    void set_camera_y(float y);
    /// \brief Get the current X translation of objects in the scene
    /// \return The current X translation
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    float camera_x() const;
    /// \brief Get the current Y translation of objects in the scene
    /// \return The current Y translation
    /// \pre Running this from any thread besides the Engine thread causes undefined behavior.
    float camera_y() const;
};

}

#endif
