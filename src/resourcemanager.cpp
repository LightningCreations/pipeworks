#include <resourcemanager.hpp>
#include <mutex>

namespace pipeworks {

ResourceManager g_resourcemanager;

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
    for(const auto &[key, data] : m_loaded_imagedata) {
        delete data;
    }
}

ImageData &ResourceManager::image_data(const std::string &name) {
    std::shared_lock lock(m_access_mutex);
    return *m_loaded_imagedata.find(name)->second;
}

bool ResourceManager::is_image_data_loaded(const std::string &name) {
    std::shared_lock lock(m_access_mutex);
    return m_loaded_imagedata.contains(name);
}

void ResourceManager::put_image_data(const std::string &name, ImageData *data) {
    std::unique_lock lock(m_access_mutex);
    m_loaded_imagedata[name] = data;
}

} // namespace pipeworks
