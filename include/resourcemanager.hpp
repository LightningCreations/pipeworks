#ifndef PW_RESOURCEMANAGER_HPP
#define PW_RESOURCEMANAGER_HPP

#include <atomic>
#include <map>
#include <shared_mutex>
#include <string>

#include "audiodata.hpp"
#include "imagedata.hpp"

namespace pipeworks {

/// \brief Thread-safe manager for data used by \ref GameObject "GameObjects"
class ResourceManager {
  private:
    std::map<std::string, AudioData*> m_loaded_audiodata;
    std::map<std::string, ImageData*> m_loaded_imagedata;
    std::shared_mutex m_access_mutex;
  public:
    /// \brief Create a ResourceManager.
    ResourceManager();
    /// \brief Deallocate loaded resources.
    ~ResourceManager();
    /// \brief Get AudioData corresponding to a name.
    /// \param name The name of a file that the image was loaded from.
    /// \return The AudioData corresponding to the file.
    /// \pre The resource must be loaded. If it isn't, the behavior is undefined.
    ///
    /// This function is thread-safe.
    AudioData &audio_data(const std::string &name);
    /// \brief Determine if there is AudioData loaded corresponding to a name.
    /// \param name The name of a file that the image would be loaded from.
    /// \return `true` if the image is loaded, `false` otherwise.
    ///
    /// This function is thread-safe.
    bool is_audio_data_loaded(const std::string &name);
    /// \brief Add loaded AudioData corresponding to a name.
    /// \param name The name of a file that the image was loaded from.
    /// \param audiodata The AudioData corresponding to the file.
    ///
    /// This function is thread-safe.
    void put_audio_data(const std::string &name, AudioData *audiodata);
    /// \brief Get ImageData corresponding to a name.
    /// \param name The name of a file that the image was loaded from.
    /// \return The ImageData corresponding to the file.
    /// \pre The resource must be loaded. If it isn't, the behavior is undefined.
    ///
    /// This function is thread-safe.
    ImageData &image_data(const std::string &name);
    /// \brief Determine if there is ImageData loaded corresponding to a name.
    /// \param name The name of a file that the image would be loaded from.
    /// \return `true` if the image is loaded, `false` otherwise.
    ///
    /// This function is thread-safe.
    bool is_image_data_loaded(const std::string &name);
    /// \brief Add loaded ImageData corresponding to a name.
    /// \param name The name of a file that the image was loaded from.
    /// \param imagedata The ImageData corresponding to the file.
    ///
    /// This function is thread-safe.
    void put_image_data(const std::string &name, ImageData *imagedata);
};

// \brief Global ResourceManager instance.
extern ResourceManager g_resourcemanager;

}

#endif // PW_RESOURCEMANAGER_HPP
