#ifndef PW_RESOURCEMANAGER_HPP
#define PW_RESOURCEMANAGER_HPP

#include <atomic>
#include <map>
#include <shared_mutex>
#include <string>

#include "imagedata.hpp"

namespace pipeworks {

class ResourceManager {
  private:
    std::map<std::string, ImageData*> m_loaded_imagedata;
    std::shared_mutex m_access_mutex;
  public:
    ResourceManager();
    ImageData &image_data(const std::string &name);
    bool image_data_loaded(const std::string &name);
    void put_image_data(const std::string &name, ImageData *imagedata);
};

extern ResourceManager g_resourcemanager;

}

#endif // PW_RESOURCEMANAGER_HPP
