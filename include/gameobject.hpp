#ifndef PW_GAMEOBJECT_HPP
#define PW_GAMEOBJECT_HPP

namespace pipeworks {

class GameObject;

}

#include <string>
#include <vector>

#include "renderer.hpp"
#include "scene.hpp"

namespace pipeworks {

/// \brief An object to be represented in the Engine.
class GameObject {
  private:
    static std::vector<std::string> empty_resource_list;
  protected:
    float m_x;
    float m_y;
    // float m_z; // Unused
    const Scene *m_scene;
  public:
    virtual ~GameObject() = 0;

    /// \brief Create a new GameObject with a given position.
    /// \param x The X position of the object.
    /// \param y The Y position of the object.
    /// \param z The Z position of the object.
    GameObject(float x, float y, float z);

    /// \brief Render this object.
    /// \param renderer The renderer to use.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// The Engine calls this from the Engine thread once per frame.
    virtual void render(Renderer &renderer) = 0;

    /// \brief Notify the object it is done loading.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    /// \pre Calling this when some dependency resources aren't loaded yet results in undefined behavior.
    ///
    /// The Engine calls this from the Engine thread when all resources from this object are loaded.
    /// The base implementation does nothing.
    virtual void finished_loading() {}

    /// \brief Determine if the GameObject's resources are all loaded.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// The base implementation has no resources to load, therefore it always returns `true`.
    virtual bool is_loaded() { return true; }

    /// \brief Get what resources may need to be loaded.
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// The base implementation has no resources to load, therefore it always returns an empty vector.
    virtual std::vector<std::string>& loadable_resources() { return empty_resource_list; }

    /// \brief Get the current (shifted) X position of the object
    /// \return The X position of this object, shifted by the active camera
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// Note: For objects that disregard the camera position, such as HUD, this function should be overriden with one that simply returns m_x.
    virtual float x() const;

    /// \brief Get the current (shifted) Y position of the object
    /// \return The Y position of this object, shifted by the active camera
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    ///
    /// Note: For objects that disregard the camera position, such as HUD, this function should be overriden with one that simply returns m_y.
    virtual float y() const;

    /// \brief Set the X position of the object
    /// \param x The new X position of this object in world space
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    void set_x(float x);

    /// \brief Set the Y position of the object
    /// \param y The new Y position of this object in world space
    /// \pre Calling this from any thread except the Engine thread results in undefined behavior.
    void set_y(float y);

    /// \brief Tell the object what scene it's in
    void bind_scene(const Scene &scene);
};

}

#endif // PW_GAMEOBJECT_HPP
