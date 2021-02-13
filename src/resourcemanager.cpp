#include <resourcemanager.hpp>

namespace pipeworks {

ResourceManager g_resourcemanager;

ResourceManager::ResourceManager() {}

ImageData &ResourceManager::image_data(const std::string &name) {
    std::shared_lock lock(m_access_mutex);
    return *m_loaded_imagedata.find(name)->second;
}

bool ResourceManager::image_data_loaded(const std::string &name) {
    std::shared_lock lock(m_access_mutex);
    return m_loaded_imagedata.contains(name);
}

void ResourceManager::put_image_data(const std::string &name, ImageData *data) {
    std::unique_lock lock(m_access_mutex);
    m_loaded_imagedata[name] = data;
}

} // namespace pipeworks
