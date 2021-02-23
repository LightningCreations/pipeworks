#ifndef PW_GAMEOBJECT_HPP
#define PW_GAMEOBJECT_HPP

namespace pipeworks {

class GameObject;

}

#include <string>
#include <vector>

#include "renderer.hpp"

namespace pipeworks {

/// \brief An object to be represented in the Engine.
class GameObject {
  public:
    virtual ~GameObject() = 0;
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
    virtual std::vector<std::string> loadable_resources() { return std::vector<std::string>(); } // Called from engine thread to determine what resources need to be loaded.
};

}

#endif // PW_GAMEOBJECT_HPP
