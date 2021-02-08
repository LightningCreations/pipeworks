#include <resourcemanager.hpp>

namespace pipeworks {

ResourceManager g_resourcemanager;

ResourceManager::ResourceManager() {}

ImageData &ResourceManager::get_image_data(const std::string &name) {
    std::shared_lock lock(access_mutex);
    return *loaded_imagedata.find(name)->second;
}

bool ResourceManager::is_image_data_loaded(const std::string &name) {
    std::shared_lock lock(access_mutex);
    return loaded_imagedata.contains(name);
}

void ResourceManager::put_image_data(const std::string &name, ImageData *data) {
    std::unique_lock lock(access_mutex);
    loaded_imagedata[name] = data;
}

}
