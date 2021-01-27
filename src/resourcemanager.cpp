#include <resourcemanager.hpp>

namespace pipeworks {

ResourceManager g_resourcemanager;

ResourceManager::ResourceManager() {}

ImageData &ResourceManager::get_imagedata(std::string name) {
    return loaded_imagedata.find(name)->second;
}

bool ResourceManager::is_imagedata_loaded(std::string name) {
    return loaded_imagedata.contains(name);
}

}
